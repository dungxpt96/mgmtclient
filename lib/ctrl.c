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
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#include "ctrl.h"


/**
 * Create a new listening Unix socket for control protocol.
 *
 * @param name The name of the Unix socket.
 * @return The socket when successful, -1 otherwise.
 */
int
ctl_create(const char *name)
{
	int s;
	struct sockaddr_un su;
	int rc;

    ctl_cleanup(name);

	if ((s = socket(PF_UNIX, SOCK_STREAM, 0)) == -1)
		return -1;

	if (fcntl(s, F_SETFD, FD_CLOEXEC) == -1) {
		close(s);
		return -1;
	}

	su.sun_family = AF_UNIX;
	strcpy(su.sun_path, name);
	if (bind(s, (struct sockaddr *)&su, sizeof(struct sockaddr_un)) == -1) {
		rc = errno; close(s); errno = rc;
		return -1;
	}

	if (listen(s, 10) == -1) {
		rc = errno; close(s); errno = rc;
		return -1;
	}

	return s;
}

/**
 * Connect to the control Unix socket.
 *
 * @param name The name of the Unix socket.
 * @return The socket when successful, -1 otherwise.
 */
int
ctl_connect(const char *name)
{
	int s;
	struct sockaddr_un su;
	int rc;

	if ((s = socket(PF_UNIX, SOCK_STREAM, 0)) == -1)
		return -1;

	su.sun_family = AF_UNIX;
	strcpy(su.sun_path, name);
	if (connect(s, (struct sockaddr *)&su, sizeof(struct sockaddr_un)) == -1) {
		rc = errno; close(s); errno = rc;
        return -1;
	}
	return s;
}

/**
 * Remove the control Unix socket.
 *
 * @param fd The file descriptor of the Unix socket.
 */
int
ctl_accept(int fd)
{
    return accept(fd, NULL, NULL);
}

/**
 * Remove the control Unix socket.
 *
 * @param name The name of the Unix socket.
 */
void
ctl_cleanup(const char *name)
{
	unlink(name);
}