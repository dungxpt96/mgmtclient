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

#include <string.h>
#include <limits.h>

#include "show.h"

static int
cmd_show_freq_sync_interface(struct writer *w,
    struct cmd_env *env, void *arg)
{

    return 1;
}

static int
cmd_show_freq_sync_interface_all(struct writer *w,
    struct cmd_env *env, void *arg)
{

    return 1;
}

static int
cmd_show_freq_sync_interface_brief(struct writer *w,
    struct cmd_env *env, void *arg)
{

    return 1;
}

static void _register_freq_sync_commands_show(struct cmd_node *root)
{
    /* show frequency synchronization interface */
	cmd_restrict_ports(root);

	commands_new(
		root,
		NEWLINE,
		"Show frequency synchronization interface information",
		cmd_check_env, cmd_show_freq_sync_interface, "interface");

    struct cmd_node *interfaces = commands_new(
		root,
		"interfaces",
		"Show frequency synchronization interface information",
		cmd_check_no_env, NULL, "interface");

    commands_new(
		interfaces,
		NEWLINE,
		"Show frequency synchronization interface information",
		NULL, cmd_show_freq_sync_interface_all, NULL);

    /* show frequency synchronization interface brief */
    struct cmd_node *interface_brief = commands_new(
		interfaces,
		"brief",
		"Show brief interface information",
		NULL, NULL, NULL);

    commands_new(
		interface_brief,
		NEWLINE,
		"Show brief interface information",
		NULL, cmd_show_freq_sync_interface_brief, NULL);
}

void register_freq_sync_commands_show(struct cmd_node *root)
{
    /* show frequency */
    struct cmd_node *frequency = commands_new(
		root,
		"frequency",
		"Frequency related show commands",
		NULL, NULL, NULL);

    /* show frequency synchronization */
    struct cmd_node *synchronization = commands_new(
		frequency,
		"synchronization",
		"Frequency Synchronization show commands",
		NULL, NULL, NULL);

    /* show frequency synchronization DATA */
    _register_freq_sync_commands_show(synchronization);
}