/*
 * rprintmsg.c: remote version of printmsg.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "msg.h"

int main(int argc, char *argv[])
{
    CLIENT *cl;
    int *result;
    char *server;
    char *message;

    if (argc < 3)
    {
        fprintf(stderr, "usage: %s <host> <message>\n", argv[0]);
        exit(1);
    }

    server = argv[1];
    message = argv[2];

    cl = clnt_create(server, MESSAGEPROG, MESSAGEVERS, "tcp");
    if (cl == NULL)
    {
        clnt_pcreateerror(server);
        exit(1);
    }

    result = printmessage_1(&message, cl);
    if (result == NULL)
    {
        clnt_perror(cl, server);
        exit(1);
    }

    if (*result == 0)
    {
        fprintf(stderr, "%s: %s unable to print message\n", argv[0], server);
        exit(1);
    }

    printf("Message delivered to %s\n", server);
    return 0;
}
