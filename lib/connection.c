/*
 * Copyright (c) 2023 Bernard Nguyen <dungxpt96@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */


#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <errno.h>

#include "../log.h"

#include "connection.h"
#include "ctrl.h"

const char *
connection_get_default_transport(void)
{
    return DAEMON_CTL_SOCKET;
}

static int
connection_sync_connect(connection_t *connect)
{
	return ctl_connect(connect->ctlname);
}

/* Synchronously send data to remote end. */
static ssize_t
connection_sync_send(connection_t *connect,
    const uint8_t *data, size_t length, void *user_data)
{
	struct connection_socker_t *socket = user_data;
	ssize_t nb;

    //printf("===> sending to fd %d with length %ld\n", socket->fd, length);

	if (socket->fd == -1 &&
	    ((socket->fd = connection_sync_connect(connect)) == -1)) {
		return 1;
	}

	while ((nb = write(socket->fd, data, length)) == -1) {
		if (errno == EAGAIN || errno == EINTR) continue;
		return 1;
	}

    //printf("===> sent to fd %d with nb %ld\n", socket->fd, nb);

	return nb;
}

static ssize_t
connection_sync_recv(connection_t *connect,
    uint8_t *data, size_t length, void *user_data)
{
	struct connection_socker_t *socket = user_data;
    size_t bytes;
    size_t pos;
    int count;
    fd_set readfds, writefds;
    struct timeval timeout;

    pos = 0;

	if (socket->fd == -1 &&
	    ((socket->fd = connection_sync_connect(connect)) == -1)) {
		return 1;
	}

    //printf("<=== ready to receive from fd %d with length %ld\n", socket->fd, length);

    do {
        //fprintf(stdout, "Receiving buffer from fd %d\n", sockfd);

        bytes = read(socket->fd, data+pos, length-pos);
        if (bytes < 0) {
            fprintf(stderr, "recv error\n");
            break;
        } else if (bytes == 0) {
            /* No data left, jump out */
            break;
        } else {
            pos += bytes;
            if (pos >= length) {
                /* The buffer is full, jump out */
                break;
            }
        }

        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        FD_SET(socket->fd, &readfds);

        timeout.tv_sec = 0;
        timeout.tv_usec = 10*1000;

        count = select(socket->fd + 1, &readfds, &writefds, (fd_set *)0, &timeout);
        if (count <= 0)  {
            break;
        }
    } while (count > 0);

    //printf("<=== received from fd %d with length %ld\n", socket->fd, pos);

    return pos;
}   

connection_t *connection_new_name(const char *ctlname,
                                    connection_send_callback send,
                                    connection_recv_callback recv,
                                    void *user_data)
{
	connection_t *conn = NULL;
	struct connection_socker_t *data = NULL;

	/* Both callbacks are mandatory or should be NULL. */
	if (send && !recv) return NULL;
	if (recv && !send) return NULL;

	if ((conn = calloc(1, sizeof(connection_t))) == NULL)
		return NULL;

	conn->ctlname = strdup(ctlname);
	if (conn->ctlname == NULL) {
		free(conn);
		return NULL;
	}
	if (!send && !recv) {
		if ((data = malloc(sizeof(struct connection_socker_t))) == NULL) {
			free(conn->ctlname);
			free(conn);
			return NULL;
		}
		data->fd = -1;
		conn->send = connection_sync_send;
		conn->recv = connection_sync_recv;
		conn->user_data = data;
	} else {
		conn->send = send;
		conn->recv = recv;
		conn->user_data = user_data;
	}

    conn->len_in = MESSAGE_MAX_LEN;
    conn->len_out = MESSAGE_MAX_LEN;

    conn->pnt_in = conn->buf_in;
    conn->pnt_out = conn->buf_out;

    //printf("Connection name %s is established\n", conn->ctlname);

	return conn;
}

int
connection_close(connection_t *conn)
{
	if (conn == NULL)
        return 0;

    if (conn->send == connection_sync_send) {
		struct connection_socker_t *data = conn->user_data;
		
        if (data->fd != -1) {
            close(data->fd);
            data->fd = -1;
        }
		
	}

    return 0;
}

int
connection_release(connection_t *conn)
{
	if (conn == NULL)
        return 0;
	
    free(conn->ctlname);
	
    if (conn->send == connection_sync_send) {
		struct connection_socker_t *data = conn->user_data;
		
        if (data->fd != -1)
            close(data->fd);
		
        free(conn->user_data);
	}

	free(conn);

	return 0;
}

/**
 * Request some bytes if they are not already here.
 *
 * @param conn   The connection to daemon.
 * @param length The number of requested bytes.
 * @return A negative integer if we can't have the bytes or the number of bytes we got.
 */
ssize_t
connection_needs(connection_t *conn, size_t length)
{
	uint8_t *buffer = NULL;
	ssize_t  rc;

	if ((buffer = malloc(length)) == NULL)
		return 1;
	rc = conn->recv(conn, buffer, length, conn->user_data);
	if (rc < 0) {
		free(buffer);
		return 1;
	}
	if (rc == 0) {
		free(buffer);
		return 1;
	}
	rc = connection_recv(conn, buffer, rc);
	free(buffer);
	if (rc < 0)
		return 1;

    conn->size_in = rc;

	return rc;
}

ssize_t
connection_recv(connection_t *conn, const uint8_t *data, size_t length)
{
	if (length == 0)
        return 0;

	/* Received data should be appended to the input buffer. */
	memcpy(conn->buf_in + conn->size_in, data, length);
	conn->size_in += length;

	return conn->size_in;
}

ssize_t
connection_send(connection_t *conn)
{
	/* Send waiting data. */
	ssize_t rc;

	rc = conn->send(conn,
	                    conn->buf_out, conn->size_out,
	                    conn->user_data);
	if (rc < 0)
        return 1;

	return rc;
}

connection_t *
connection_create()
{
    return connection_new_name(connection_get_default_transport(),
                    NULL, NULL, NULL);
}