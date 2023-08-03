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

#ifndef _FREQUENCY_SYNCHRONIZATION_DISPLAY_H
#define _FREQUENCY_SYNCHRONIZATION_DISPLAY_H

#include "../../../client.h"

void 
display_freq_sync_interface_spec(struct writer *,
    struct cmd_env *);

void 
display_freq_sync_interfaces_all(struct writer *,
    struct cmd_env *);

void 
display_freq_sync_interfaces_brief(struct writer *,
    struct cmd_env *);


#endif /* _FREQUENCY_SYNCHRONIZATION_DISPLAY_H */