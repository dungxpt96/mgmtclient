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

#include "client.h"
#include <string.h>
#include <limits.h>

#include "daemon/freqsync/show/freqsync_show.h"

struct register_command_s
{
    int daemon;
    void (*show)(struct cmd_node *root);
};
static struct register_command_s register_command_tb[] =
{
    {DAEMON_FREQUENCY_SYNCHRONIZATION,             register_freq_sync_commands_show}
};

static void register_daemon_commands_show(struct cmd_node *root)
{
    int daemon_id = 0;

    for (daemon_id = DAEMON_MIN; daemon_id < DAEMON_MAX; daemon_id++) {
        if (register_command_tb[daemon_id].show) {
            register_command_tb[daemon_id].show(root);
        }
    }
}

void register_commands_show(struct cmd_node *root)
{
	struct cmd_node *show = commands_new(
		root,
		"show",
		"Show running system information",
		NULL, NULL, NULL);

    register_daemon_commands_show(show);
}