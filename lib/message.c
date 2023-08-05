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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "connection.h"
#include "message.h"
#include "tlv.h"

int
message_encode_header (uint8_t **pnt, uint16_t *size,
                   struct hmsg_header *header)
{
  uint8_t *sp = *pnt;

  if (*size < MSG_HEADER_SIZE) {
    printf("Packet too short!!!\n");
    return -1;
  }

  TLV_ENCODE_PUTW (header->type);
  TLV_ENCODE_PUTW (header->length);

  return *pnt - sp;
}

int
message_decode_header (uint8_t **pnt, uint16_t *size,
                   struct hmsg_header *header)
{
  if (*size < MSG_HEADER_SIZE) {
    printf("Packet too short!!!\n");
    return -1;
  }

  TLV_DECODE_GETW (header->type);
  TLV_DECODE_GETW (header->length);

  return MSG_HEADER_SIZE;
}

message_set_handler(connection_t *conn, int message_type,
                        CONN_PARSER parser,
                        CONN_CALLBACK callback)
{
    conn->parser[message_type] = parser;
    conn->callback[message_type] = callback;
}

void
message_set_callback (connection_t *conn, int message_type,
                         CONN_CALLBACK callback)
{
    conn->callback[message_type] = callback;
}

void
message_set_parser (connection_t *conn, int message_type,
                         CONN_PARSER parser)
{
    conn->parser[message_type] = parser;
}

void message_send(connection_t *conn, int message_type, uint16_t len)
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

    message_recv(conn);

    connection_close(conn);
}

void message_recv(connection_t *conn)
{
    struct hmsg_header header;
    int rc;

    rc = connection_needs(conn, MESSAGE_MAX_LEN);
    
    message_decode_header (&conn->pnt_in, &conn->size_in, &header);

    printf("Decode header message_type: %d length=%d\n", header.type, header.length);

    if (conn->callback[header.type] != NULL) {
        (*conn->parser[header.type])(&conn->pnt_in, &conn->size_in, &header,
                                        conn, conn->callback[header.type]);
    }
}