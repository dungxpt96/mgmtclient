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

#ifndef _CLIENT_H
#define _CLIENT_H

#include "lib/connection.h"

#include "writer.h"
#include "log.h"
#include "compat/compat.h"

#ifdef HAVE_ADDRESS_SANITIZER
# include <sanitizer/lsan_interface.h>
# define SUPPRESS_LEAK(x) __lsan_ignore_object(x)
#else
# define SUPPRESS_LEAK(x)
#endif

extern const char *ctlname;

/* commands.c */
#define CMD_NEWLINE "<CR>"

enum daemons
{
    DAEMON_MIN = 0,

    DAEMON_FREQUENCY_SYNCHRONIZATION = DAEMON_MIN,

    DAEMON_MAX
};

struct cmd_node;
struct cmd_env;

struct cmd_node *commands_root(void);

struct cmd_node *commands_new(
	struct cmd_node *,
	const char *,
	const char *,
	int(*validate)(struct cmd_env*, void *),
	int(*execute)(connection_t *, struct writer*,
	    struct cmd_env*, void *),
	void *);

struct cmd_node* commands_privileged(struct cmd_node *);

struct cmd_node* commands_lock(struct cmd_node *);

struct cmd_node* commands_hidden(struct cmd_node *);

void commands_free(struct cmd_node *);

const char *cmdenv_arg(struct cmd_env*);
const char *cmdenv_get(struct cmd_env*, const char*);

int cmdenv_put(struct cmd_env*, const char*, const char*);

int cmdenv_pop(struct cmd_env*, int);

int commands_execute(connection_t *conn, struct writer *,
    struct cmd_node *, int, const char **, int);

char *commands_complete(struct cmd_node *, int, const char **,
    int, int);

/* helpers */
int cmd_check_no_env(struct cmd_env *, void *);
int cmd_check_env(struct cmd_env *, void *);
int cmd_store_env(struct writer *,
    struct cmd_env *, void *);
int cmd_store_env_and_pop(connection_t *conn, struct writer *,
    struct cmd_env *, void *);
int cmd_store_env_value(connection_t *conn, struct writer *,
    struct cmd_env *, void *);
int cmd_store_env_value_and_pop(connection_t *conn, struct writer *,
    struct cmd_env *, void *);
int cmd_store_env_value_and_pop2(connection_t *conn, struct writer *,
    struct cmd_env *, void *);
int cmd_store_env_value_and_pop3(connection_t *conn, struct writer *,
    struct cmd_env *, void *);
int cmd_store_something_env_value_and_pop2(connection_t *conn, const char *, struct cmd_env *,
    void *);
int cmd_store_something_env_value(connection_t *conn, const char *, struct cmd_env *,
    void *);

void cmd_restrict_ports(struct cmd_node *);

/* show.c */
void register_commands_show(struct cmd_node *);

/* configure.c */
void register_commands_configure(struct cmd_node *);

/* tokenizer.c */
int tokenize_line(const char*, int*, char***);
void tokenize_free(int, char**);

#endif
