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

#ifndef _LIB_CONNECTION_H
#define _LIB_CONNECTION_H

#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <ctype.h>
#include <pthread.h>

#include "message.h"

#if defined (LIBFREQSYNC)
#define DAEMON_CTL_SOCKET       FREQSYNC_CTL_SOCKET
#else
#define DAEMON_CTL_SOCKET       "mgmtclient_connection.socket"
#endif

struct connection_socker_t {
	int fd;			/* File descriptor to the socket. */
};

typedef struct connection_t connection_t;

/**
 * Callback function invoked to send data to daemon.
 *
 * @param conn      Handle to the connection to daemon.
 * @param data      Bytes to be sent.
 * @param length    Length of provided data.
 * @param user_data Provided user data.
 * @return The number of bytes really sent
 */
typedef ssize_t (*connection_send_callback)(connection_t *conn,
    const uint8_t *data, size_t length, void *user_data);

/**
 * Callback function invoked to receive data from daemon.
 *
 * @param conn      Handle to the connection to daemon.
 * @param data      Buffer for receiving data
 * @param length    Maximum bytes we can receive
 * @param user_data Provided user data.
 * @return The number of bytes really received 
 */
typedef ssize_t (*connection_recv_callback)(connection_t *conn,
    uint8_t *data, size_t length, void *user_data);

struct connection_t {
	/* the Unix-domain socket to connect to daemon */
	char *ctlname;

    pthread_t thread_id;

	/* Callback handling */
	connection_recv_callback recv; /* Receive callback */
	connection_send_callback send; /* Send callback */
	void *user_data;	    /* Callback user data */

    /* Message buffer for output. */
    uint8_t buf_out[MESSAGE_MAX_LEN];
    uint16_t len_out;
    uint8_t *pnt_out;
    uint16_t size_out;

    /* Message buffer for input. */
    uint8_t buf_in[MESSAGE_MAX_LEN];
    uint16_t len_in;
    uint8_t *pnt_in;
    uint16_t size_in;

    CONN_PARSER parser[MESSAGE_MAX];

    CONN_CALLBACK callback[MESSAGE_MAX];
};

const char *
connection_get_default_transport(void);

/**
 * Allocate a new handler for connecting to daemon.
 *
 * @param  ctlname   the Unix-domain socket to connect to daemon.
 * @param  send      Callback to be used when sending   new data is requested.
 * @param  recv      Callback to be used when receiving new data is requested.
 * @param  user_data Data to pass to callbacks.
 * @return An handler to be used to connect to daemon
 *
 * The allocated handler can be released with @c connection_release(). If the
 * provided parameters are both @c NULL, default synchronous callbacks will be
 * used.
 */
connection_t *connection_new_name(const char *ctlname,
                                    connection_send_callback send,
                                    connection_recv_callback recv,
                                    void *user_data);

int
connection_close(connection_t *conn);

/**
 * Release resources associated with a connection to daemon.
 *
 * @param   conn Previously allocated handler to a connection to daemon.
 * @return  0 on success or a negative integer
 *
 * @see connection_new()
 */
int connection_release(connection_t *conn);

ssize_t connection_needs(connection_t *conn, size_t length);

/**
 * Function invoked when additional data is available from daemon.
 *
 * This function should be invoked in case of asynchronous IO when new data is
 * available from daemon (expected or unexpected).
 *
 * @param  conn      Handle to the connection to daemon.
 * @param  data      Data received from daemon.
 * @param  length    Length of data received.
 * @return The number of bytes available or a negative integer if an error has
 *         occurred. 0 is not an error. It usually means that a notification has
 *         been processed.
 */
ssize_t connection_recv(connection_t *conn, const uint8_t *data, size_t length);

/**
 * Function invoked when there is an opportunity to send data to daemon.
 *
 * This function should be invoked in case of asynchronous IO when new data can
 * be written to daemon.
 *
 * @param  conn  Handle to the connection to daemon.
 * @return The number of bytes processed or a negative integer if an error has
 *         occurred.
 */
ssize_t connection_send(connection_t *conn);

connection_t *connection_create();

#endif /* _LIB_CONNECTION_H */