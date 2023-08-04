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

#include "daemon/freqsync/configure/freqsync_configure.h"

extern char hostname[256];

struct register_command_s
{
    int daemon;
    void (*configure)(struct cmd_node *root);
};
static struct register_command_s register_command_tb[] =
{
    {DAEMON_FREQUENCY_SYNCHRONIZATION,             register_freq_sync_commands_configure}
};

static void register_daemon_commands_configure(struct cmd_node *root)
{
    int daemon_id = 0;

    for (daemon_id = DAEMON_MIN; daemon_id < DAEMON_MAX; daemon_id++) {
        if (register_command_tb[daemon_id].configure) {
            register_command_tb[daemon_id].configure(root);
        }
    }
}

static int
cmd_configure_hostname(struct writer *w,
    struct cmd_env *env, void *arg)
{
	strcpy(hostname, cmdenv_get(env, "hostname"));

    return 1;
}

static void _register_configure_hostname(struct cmd_node *root)
{
	struct cmd_node *hostname = commands_new(
		root,
		"hostname",
		"Hostname of the host",
		NULL, NULL, NULL);

	commands_new(
		hostname,
		NULL,
		"Hostname of the host",
		NULL, cmd_store_env_value_and_pop, "hostname");

	commands_new(
		hostname,
		NEWLINE,
		"Hostname of the host",
		cmd_check_env, cmd_configure_hostname, "hostname");
}

void register_commands_configure(struct cmd_node *root)
{
	struct cmd_node *configure = commands_new(
		root,
		"configure",
		"Change system settings",
		NULL, NULL, NULL);

	struct cmd_node *unconfigure = commands_new(
		root,
		"unconfigure",
		"Unconfigure system settings",
		NULL, NULL, NULL);

    register_daemon_commands_configure(configure);
    register_daemon_commands_configure(unconfigure);

    _register_configure_hostname(configure);
}