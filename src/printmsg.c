/*
 * printmsg.c print a message on the console
 */

#include <stdio.h>
#include <stdlib.h>

int printmsg(char *msg);

int main(int argc, char *argv[])
{
	char *msg;

	if (argc < 2) 
	{
        fprintf(stderr, "usage: %s <message>\n", argv[0]);
        exit(1);
	}

    msg = argv[1];

    if(!printmsg(msg))
    {
        fprintf(stderr, "%s unable to print message\n", argv[0]);
        exit(1); 
    }

    printf("Message Delivered\n");
    return 0;
}

int printmsg(char *msg)
{
    FILE *fp;
    fp = fopen("/dev/tty", "w");  // deviates from guide, /dev/console which is root only
    if (fp == NULL)
    {
        return 0;
    }
    fprintf(fp, "%s\n", msg);
    fclose(fp);
    return (1);
}
