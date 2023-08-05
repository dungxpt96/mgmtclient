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

#include <sys/prctl.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#include "mgmt_server.h"
#include "lib/connection.h"

#define UNUSED(var) (void)(var)

static int running = 1;

static void handle_int_quit_term(int s)
{
	UNUSED(s);

	running = 0;
}

int handle_term_signals(void)
{
	if (SIG_ERR == signal(SIGINT, handle_int_quit_term)) {
		fprintf(stderr, "cannot handle SIGINT\n");
		return -1;
	}
	if (SIG_ERR == signal(SIGQUIT, handle_int_quit_term)) {
		fprintf(stderr, "cannot handle SIGQUIT\n");
		return -1;
	}
	if (SIG_ERR == signal(SIGTERM, handle_int_quit_term)) {
		fprintf(stderr, "cannot handle SIGTERM\n");
		return -1;
	}
	if (SIG_ERR == signal(SIGHUP, handle_int_quit_term)) {
		fprintf(stderr, "cannot handle SIGHUP\n");
		return -1;
	}
	return 0;
}

int is_running(void)
{
	return running;
}

typedef struct
{
    pthread_t thread_id;
    pthread_cond_t condition;
    pthread_mutex_t mutex;
} pll_thread_info_t;

static connection_t *server_conn = NULL;
static pll_thread_info_t server_thread;

static void
mgmt_server_pthread_error(const int create_rv)
{
    fprintf(stderr, "Could not create thread.");
    switch (create_rv)
    {
        case EAGAIN:
            fprintf(stderr, "Insufficient resources to create another thread or a system-imposed limit on the number of threads was encountered.");
            break;
        case EINVAL:
            fprintf(stderr, "Invalid settings in attr.");
            break;
        case EPERM:
            fprintf(stderr, "No permission to set the scheduling policy and parameters specified in attr.");
            break;
        default:
            break;
    }
}

static int
mgmt_server_pthread_setname (char const *name)
{
    char name_buf[64] = {0};

    if(name == NULL)
        return 1;

    if(strcmp("Main", name) == 0)
        return 0;

    snprintf(name_buf, sizeof(name_buf) - 1, "%s_%s",
        "mgmt_server_thread", name);

    if (prctl(PR_SET_NAME, name_buf) < 0)
        return 1;

    return 0;
}

static void test_reply(connection_t *conn, int message_type, uint16_t len)
{
    struct hmsg_header header;
    uint16_t size;
    uint8_t *pnt;
    int ret;
    int rc;

    pnt = conn->buf_out;
    size = MSG_HEADER_SIZE;

    header.type = message_type;
    header.length = len + MSG_HEADER_SIZE;

    conn->size_out = len + MSG_HEADER_SIZE;

    message_encode_header (&pnt, &size, &header);

    connection_send(conn);
}

void *mgmt_server_handler_client(void *arg)
{
    connection_t *client_conn = (connection_t *)arg;
    struct connection_socker_t *socket = NULL;
    int clientfd = 0;
    int rc;

    socket = server_conn->user_data;
    clientfd = socket->fd;

    rc = connection_needs(client_conn, MESSAGE_MAX_LEN);

    printf("Client fd = %d sent to server length=%d\n", clientfd, rc);
    test_reply(client_conn,
                FREQSYNC_SHOW_INTERFACE_BRIEF,
                0);

    connection_release(client_conn);

    pthread_exit(0);
}

static void *
mgmt_server_run(void *data)
{
	connection_t *server_conn = (connection_t *)data;
    struct connection_socker_t *socket = NULL;
    int clientfd = 0;

    socket = server_conn->user_data;

    mgmt_server_pthread_setname("smc");

    while (is_running())
    {
        connection_t *client_conn = NULL;
        struct connection_socker_t *client_socket = NULL;

        clientfd = ctl_accept(socket->fd);

        if (clientfd < 0)
            continue;

        client_conn = connection_create();
        client_socket = client_conn->user_data;

        client_socket->fd = clientfd;
        printf("Client fd = %d connected!!! Ready to recv data\n", clientfd);

        if (pthread_create(&client_conn->thread_id, NULL,
                                mgmt_server_handler_client, client_conn) != 0) {
                fprintf(stderr, "pthread_create error\n");
                close(clientfd);
                return -1;
            }
    }

	pthread_exit(NULL);

    return NULL;
}

void mgmt_server_start()
{
    int create_rv = 0;
    struct connection_socker_t *socket = NULL;

    server_conn = connection_create();
    socket = server_conn->user_data;
    socket->fd = ctl_create(server_conn->ctlname);

    freqsync_message_register(server_conn);

    pthread_cond_init(&server_thread.condition, NULL);
    pthread_mutex_init(&server_thread.mutex, NULL);

    create_rv = pthread_create(&(server_thread.thread_id),
                    NULL, mgmt_server_run, server_conn);
    if (create_rv)
    {
        mgmt_server_pthread_error(create_rv);
    }
}

void mgmt_server_stop()
{
    pthread_cond_destroy(&server_thread.condition);
    pthread_mutex_destroy(&server_thread.mutex);

    connection_release(server_conn);
}