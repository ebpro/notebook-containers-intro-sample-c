#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Simple container demo program
 *
 * Shows how a program running inside a container can access:
 * - environment variables
 * - container hostname
 * - process information (PID, UID)
 */

int main(void)
{
    char hostname[256] = "unknown";

    if (gethostname(hostname, sizeof(hostname)) != 0)
        perror("gethostname");

    const char *name = getenv("NAME");

    printf("Hostname : %s\n", hostname);
    printf("PID      : %d\n", getpid());
    printf("UID      : %d\n", getuid());
    printf("Hello %s!\n", name ? name : "World");

    return EXIT_SUCCESS;
}
