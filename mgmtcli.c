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
#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <libgen.h>
#include <dirent.h>
#include <signal.h>
#include <sys/queue.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "client.h"

#ifdef HAVE___PROGNAME
extern const char	*__progname;
#else
# define __progname "mgmtcli"
#endif

/* Global for completion */
static struct cmd_node *root = NULL;
const char *ctlname = NULL;
char hostname[256] = "mgmtcli";

static int
is_privileged()
{
	/* Check we can access the control socket with read/write
	 * privileges. The `access()` function uses the real UID and real GID,
	 * therefore we don't have to mangle with our identity. */
	return (ctlname && access(ctlname, R_OK|W_OK) == 0);
}

static char*
prompt()
{
#define CESC "\033"
	static char hostname_priv[256] = {0};

	int privileged = is_privileged();
	if (isatty(STDIN_FILENO)) {
		if (privileged) {
			sprintf(hostname_priv, "%s # ", hostname);
			return hostname_priv;
		}

		sprintf(hostname_priv, "%s $ ", hostname);
		return hostname_priv;
	}
	return "";
}

static int must_exit = 0;
/**
 * Exit the interpreter.
 */
static int
cmd_exit(struct mgmtctl_conn_t *conn, struct writer *w,
    struct cmd_env *env, void *arg)
{
	log_info("mgmtctl", "quit mgmtcli");
	must_exit = 1;
	return 1;
}

static int
_cmd_complete(int all)
{
	char **argv = NULL;
	int argc = 0;
	int rc = 1;
	size_t len = strlen(rl_line_buffer);
	char *line = malloc(len + 2);
	if (!line) return -1;
	strlcpy(line, rl_line_buffer, len + 2);
	line[rl_point]   = 2;	/* empty character, will force a word */
	line[rl_point+1] = 0;

	if (tokenize_line(line, &argc, &argv) != 0)
		goto end;

	char *compl = commands_complete(root, argc, (const char **)argv, all, is_privileged());
	if (compl && strlen(argv[argc-1]) < strlen(compl)) {
		if (rl_insert_text(compl + strlen(argv[argc-1])) < 0) {
			free(compl);
			goto end;
		}
		free(compl);
		rc = 0;
		goto end;
	}
	/* No completion or several completion available. */
	free(compl);
	fprintf(stderr, "\n");
	rl_forced_update_display();
	rc = 0;
end:
	free(line);
	tokenize_free(argc, argv);
	return rc;
}

static int
cmd_complete(int count, int ch)
{
	return _cmd_complete(0);
}

static int
cmd_help(int count, int ch)
{
	return _cmd_complete(1);
}

/**
 * Execute a tokenized command and display its output.
 *
 * @param conn The connection to mgmtd.
 * @param fmt  Output format.
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 * @return 0 if an error occurred, 1 otherwise
 */
static int
cmd_exec(const char *fmt, int argc, const char **argv)
{
	/* Init output formatter */
	struct writer *w;

	if(strcmp(fmt, "plain") == 0) {
		w = txt_init(stdout);
	}
	else {
		log_warnx("mgmtctl", "unknown output format \"%s\"", fmt);
		w = txt_init(stdout);
	}

	/* Execute command */
	int rc = commands_execute(w,
	    root, argc, argv, is_privileged());
	if (rc != 0) {
		log_info("mgmtctl", "an error occurred while executing last command");
		w->finish(w);
		return 0;
	}
	w->finish(w);
	return 1;
}

/**
 * Execute a command line and display its output.
 *
 * @param conn The connection to mgmtd.
 * @param fmt  Output format.
 * @param line Line to execute.
 * @return -1 if an error occurred, 0 if nothing was executed. 1 otherwise.
 */
static int
parse_and_exec(const char *fmt, const char *line)
{
	int cargc = 0; char **cargv = NULL;
	int n;
	log_debug("mgmtctl", "tokenize command line");
	n = tokenize_line(line, &cargc, &cargv);
	switch (n) {
	case -1:
		log_warnx("mgmtctl", "internal error while tokenizing");
		return -1;
	case 1:
		log_warnx("mgmtctl", "unmatched quotes");
		return -1;
	}
	if (cargc != 0)
		n = cmd_exec(fmt, cargc, (const char **)cargv);
	tokenize_free(cargc, cargv);
	return (cargc == 0)?0:
	    (n == 0)?-1:
	    1;
}

static struct cmd_node*
register_commands()
{
	root = commands_root();

	register_commands_show(root);
	register_commands_configure(root);

	commands_new(
		commands_new(root, "exit", "Exit interpreter", NULL, NULL, NULL),
		NEWLINE, "Exit interpreter", NULL, cmd_exit, NULL);
	return root;
}

struct input {
	TAILQ_ENTRY(input) next;
	char *name;
};
TAILQ_HEAD(inputs, input);
static int
filter(const struct dirent *dir)
{
	if (strlen(dir->d_name) < 5) return 0;
	if (strcmp(dir->d_name + strlen(dir->d_name) - 5, ".conf")) return 0;
	return 1;
}

int
main(int argc, char *argv[])
{
	int rc = EXIT_FAILURE;
	int n;
	const char *fmt = "plain";

	signal(SIGHUP, SIG_IGN);

	/* Disable SIGPIPE */
	signal(SIGPIPE, SIG_IGN);

	/* Register commands */
	root = register_commands();

	/* Make a connection */
	log_debug("mgmtctl", "connect to mgmtd");

	/* Interactive session */
	rl_bind_key('?',  cmd_help);
	rl_bind_key('\t', cmd_complete);

	char *line = NULL;
	do {
		if ((line = readline(prompt()))) {
			int n = parse_and_exec(fmt, line);
			if (n != 0) {
				add_history(line);
			}
			free(line);
		}
	} while (!must_exit && line != NULL);
	rc = EXIT_SUCCESS;

end:
	if (root) commands_free(root);
	return rc;
}
