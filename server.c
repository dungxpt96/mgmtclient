/******************************************************************************
*
* FILENAME:
*     server.c
*
* DESCRIPTION:
*     The example of server using Unix domain socket.
*
******************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "error.h"

#include "lib/message.h"
#include "lib/connection.h"
#include "lib/ctrl.h"

#include "mgmt_server.h"

char hostname[256];

int main(void)
{
    mgmt_server_start();

    while (is_running());

    mgmt_server_stop();

    return 0;
}