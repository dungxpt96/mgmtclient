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

#ifndef _LIB_TLV_H
#define _LIB_TLV_H

#define TLV_ENCODE_CHAR(V)                                                    \
    do {                                                                      \
      *(*pnt)     = (V) & 0xFF;                                               \
      (*pnt)++;                                                               \
      (*size)--;                                                              \
    } while (0)

#define TLV_ENCODE_SHORT(V)                                                   \
    do {                                                                      \
      *(*pnt)     = ((V) >> 8) & 0xFF;                                        \
      *(*pnt + 1) = (V) & 0xFF;                                               \
      *pnt += 2;                                                              \
      *size -= 2;                                                             \
    } while (0)

#define TLV_ENCODE_INT(V)                                                     \
    do {                                                                      \
      *(*pnt)     = ((V) >> 24) & 0xFF;                                       \
      *(*pnt + 1) = ((V) >> 16) & 0xFF;                                       \
      *(*pnt + 2) = ((V) >> 8) & 0xFF;                                        \
      *(*pnt + 3) = (V) & 0xFF;                                               \
      *pnt += 4;                                                              \
      *size -= 4;                                                             \
    } while (0)

#define TLV_ENCODE_DOUBLE(V)                                                  \
    do {                                                                      \
      *(*pnt)     = ((V) >> 56) & 0xFF;                                       \
      *(*pnt + 1) = ((V) >> 48) & 0xFF;                                       \
      *(*pnt + 2) = ((V) >> 40) & 0xFF;                                       \
      *(*pnt + 3) = ((V) >> 32) & 0xFF;                                       \
      *(*pnt + 4) = ((V) >> 24) & 0xFF;                                       \
      *(*pnt + 5) = ((V) >> 16) & 0xFF;                                       \
      *(*pnt + 6) = ((V) >> 8) & 0xFF;                                        \
      *(*pnt + 7) = (V) & 0xFF;                                               \
      *pnt += 8;                                                              \
      *size -= 8;                                                             \
    } while (0)

#define TLV_ENCODE(P,L)                                                       \
    do {                                                                      \
      pal_mem_cpy ((void *)(*pnt), (void *) (P), (L));                        \
      *pnt += (L);                                                            \
      *size -= (L);                                                           \
    } while (0)

#define TLV_ENCODE_IN4_ADDR(P)                                                \
    do {                                                                      \
      *(*pnt)     = (*((uint8_t *)(P)));                                      \
      *(*pnt + 1) = (*((uint8_t *)(P) + 1));                                  \
      *(*pnt + 2) = (*((uint8_t *)(P) + 2));                                  \
      *(*pnt + 3) = (*((uint8_t *)(P) + 3));                                  \
      *pnt += 4;                                                              \
      *size -= 4;                                                             \
    } while (0)

#define TLV_ENCODE_IN6_ADDR(P)                                                \
    do {                                                                      \
      *(*pnt)     = (*((uint8_t *)(P)));                                      \
      *(*pnt + 1) = (*((uint8_t *)(P) + 1));                                  \
      *(*pnt + 2) = (*((uint8_t *)(P) + 2));                                  \
      *(*pnt + 3) = (*((uint8_t *)(P) + 3));                                  \
      *(*pnt + 4) = (*((uint8_t *)(P) + 4));                                  \
      *(*pnt + 5) = (*((uint8_t *)(P) + 5));                                  \
      *(*pnt + 6) = (*((uint8_t *)(P) + 6));                                  \
      *(*pnt + 7) = (*((uint8_t *)(P) + 7));                                  \
      *(*pnt + 8) = (*((uint8_t *)(P) + 8));                                  \
      *(*pnt + 9) = (*((uint8_t *)(P) + 9));                                  \
      *(*pnt + 10) = (*((uint8_t *)(P) + 10));                                \
      *(*pnt + 11) = (*((uint8_t *)(P) + 11));                                \
      *(*pnt + 12) = (*((uint8_t *)(P) + 12));                                \
      *(*pnt + 13) = (*((uint8_t *)(P) + 13));                                \
      *(*pnt + 14) = (*((uint8_t *)(P) + 14));                                \
      *(*pnt + 15) = (*((uint8_t *)(P) + 15));                                \
      *pnt += 16;                                                             \
      *size -= 16;                                                            \
    } while (0)

#define TLV_DECODE_CHAR(V)                                                    \
    do {                                                                      \
      (V) = **pnt;                                                            \
      (*pnt)++;                                                               \
      (*size)--;                                                              \
    } while (0)

#define TLV_DECODE_SHORT(V)                                                   \
    do {                                                                      \
      (V) = ((*(*pnt))    << 8)                                               \
          +  (*(*pnt + 1));                                                   \
      *pnt += 2;                                                              \
      *size -= 2;                                                             \
    } while (0)

#define TLV_DECODE_INT(V)                                                     \
    do {                                                                      \
      (V) = (uint32_t)((*(*pnt))     << 24)                                   \
          + (uint32_t)((*(*pnt + 1)) << 16)                                   \
          + (uint32_t)((*(*pnt + 2)) << 8)                                    \
          + (uint32_t)(*(*pnt + 3));                                          \
      *pnt += 4;                                                              \
      *size -= 4;                                                             \
    } while (0)

#define TLV_DECODE_DOUBLE(V)                                                  \
    do {                                                                      \
      (V) = (uint32_t)((*(*pnt))     << 24)                                   \
          + (uint32_t)((*(*pnt + 1)) << 16)                                   \
          + (uint32_t)((*(*pnt + 2)) << 8)                                    \
          + (uint32_t)((*(*pnt + 3)));                                        \
      (V) = (V) << 32;                                                        \
      uint32_t temp = 0;                                                      \
      temp = (uint32_t)((*(*pnt + 4)) << 24)                                  \
           + (uint32_t)((*(*pnt + 5)) << 16)                                  \
           + (uint32_t)((*(*pnt + 6)) << 8)                                   \
           + (uint32_t)(*(*pnt + 7));                                         \
      (V) = (V) + (uint64_t)temp;                                             \
      *pnt += 8;                                                              \
      *size -= 8;                                                             \
    } while (0)

#define TLV_DECODE(P,L)                                                       \
    do {                                                                      \
      pal_mem_cpy ((void *) (P), *pnt, (L));                                  \
      *pnt += (L);                                                            \
      *size -= (L);                                                           \
    } while (0)

#define TLV_DECODE_IN4_ADDR(P)                                                \
    do {                                                                      \
      (*((uint8_t *)(P)))     = *(*pnt);                                      \
      (*((uint8_t *)(P) + 1)) = *(*pnt + 1);                                  \
      (*((uint8_t *)(P) + 2)) = *(*pnt + 2);                                  \
      (*((uint8_t *)(P) + 3)) = *(*pnt + 3);                                  \
      *pnt += 4;                                                              \
      *size -= 4;                                                             \
    } while (0)

#define TLV_DECODE_IN6_ADDR(P)                                                \
    do {                                                                      \
      (*((uint8_t *)(P)))     = *(*pnt);                                      \
      (*((uint8_t *)(P) + 1)) = *(*pnt + 1);                                  \
      (*((uint8_t *)(P) + 2)) = *(*pnt + 2);                                  \
      (*((uint8_t *)(P) + 3)) = *(*pnt + 3);                                  \
      (*((uint8_t *)(P) + 4)) = *(*pnt + 4);                                  \
      (*((uint8_t *)(P) + 5)) = *(*pnt + 5);                                  \
      (*((uint8_t *)(P) + 6)) = *(*pnt + 6);                                  \
      (*((uint8_t *)(P) + 7)) = *(*pnt + 7);                                  \
      (*((uint8_t *)(P) + 8)) = *(*pnt + 8);                                  \
      (*((uint8_t *)(P) + 9)) = *(*pnt + 9);                                  \
      (*((uint8_t *)(P) + 10)) = *(*pnt + 10);                                \
      (*((uint8_t *)(P) + 11)) = *(*pnt + 11);                                \
      (*((uint8_t *)(P) + 12)) = *(*pnt + 12);                                \
      (*((uint8_t *)(P) + 13)) = *(*pnt + 13);                                \
      (*((uint8_t *)(P) + 14)) = *(*pnt + 14);                                \
      (*((uint8_t *)(P) + 15)) = *(*pnt + 15);                                \
      *pnt += 16;                                                             \
      *size -= 16;                                                            \
    } while (0)

#endif /* _LIB_TLV_H */