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

#ifndef _LIB_DAEMON_CLIENT_
#define _LIB_DAEMON_CLIENT_

#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <ctype.h>

typedef enum message_type
{
    FREQSYNC_SHOW_INTERFACE_BRIEF = 10,
} message_type_e;

struct hmsg_header {
	uint16_t type;
	uint16_t length;
};

struct connection_t;

typedef int (*CONN_CALLBACK) (struct hmsg_header *, void *, void *);

typedef int (*CONN_PARSER) (uint8_t **, u_int16_t *, struct hmsg_header *,
                           void *, CONN_CALLBACK);

#define MSG_HEADER_SIZE   4

#define MESSAGE_MAX_LEN     4096
#define MESSAGE_MAX         1000

int
message_encode_header (uint8_t **pnt, uint16_t *size,
                   struct hmsg_header *header);
int
message_decode_header (uint8_t **pnt, uint16_t *size,
                   struct hmsg_header *header);

void
message_set_handler(struct connection_t *conn, int message_type,
                        CONN_PARSER parser,
                        CONN_CALLBACK callback);


void
message_set_callback (struct connection_t *conn, int message_type,
                         CONN_CALLBACK callback);

void
message_set_parser (struct connection_t *conn, int message_type,
                         CONN_PARSER parser);

void
message_send(struct connection_t *conn, int message_type,
                         uint16_t len);

void message_recv(struct connection_t *conn);

#endif /* _LIB_DAEMON_CLIENT_ */