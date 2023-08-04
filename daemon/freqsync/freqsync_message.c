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

#include "freqsync_message.h"

#include "../../lib/message.h"
#include "../../client.h"

int
freqsync_encode_show_interface_brief (uint8_t **pnt, u_int16_t *size)
{
    uint8_t *sp = *pnt;

    printf("%s: %d\n", __FUNCTION__, __LINE__);

    return *pnt - sp;
}

int
freqsync_decode_show_interface_brief (uint8_t **pnt, u_int16_t *size)
{
    uint8_t *sp = *pnt;

    printf("%s: %d\n", __FUNCTION__, __LINE__);

    return *pnt - sp;
}

int
freqsync_parse_show_interface_brief(uint8_t **pnt, uint16_t *size, struct hmsg_header *header,
                           void *arg, CONN_CALLBACK callback)
{
    printf("%s: %d *size=%d\n", __FUNCTION__, __LINE__, *size);

    freqsync_decode_show_interface_brief(pnt, size);

    if (callback != NULL) {
        (*callback)(header, arg, NULL);
    }
    return 0;
}

int
freqsync_callback_show_interface_brief(struct hmsg_header *header, void *arg, void *message)
{
    printf("%s: %d\n", __FUNCTION__, __LINE__);
    return 0;
}

void
freqsync_message_register(connection_t *conn)
{
    message_set_handler(conn, FREQSYNC_SHOW_INTERFACE_BRIEF,
                            freqsync_parse_show_interface_brief,
                            freqsync_callback_show_interface_brief);
}

/* --------------------------------------------------------------------*/
/* ------------------- Handle specific message ------------------------*/
/* --------------------------------------------------------------------*/

static void freqsync_message_recv_message(connection_t *conn)
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

static void freqsync_message_send_message(connection_t *conn, int message_type, uint16_t len)
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

    freqsync_message_recv_message(conn);

    connection_close(conn);
}

void freqsync_message_send_interfaces_brief(connection_t *conn)
{
    uint16_t size;
    uint8_t *pnt;
    uint16_t nbytes = 0;

    pnt = conn->buf_out + MSG_HEADER_SIZE;
    size = conn->len_out - MSG_HEADER_SIZE;

    /*
        TODO: Encode data buffer if have
        struct messageXXX msg;

        nbytes = encode_something (&pnt, &size, msg);
        if (nbytes < 0)
            return nbytes;
    */

   return freqsync_message_send_message(conn,
                                        FREQSYNC_SHOW_INTERFACE_BRIEF,
                                        nbytes);
}