#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "scanner.h"
#include "utils.h"
#include "threads.h"

/*
argv[0] -> Program Name
argv[1] -> IP Address
*/

int main(int argc, char const *argv[])
{

    // Invalid usage
    if (argc != 4)
    {
        printf("Usage: %s <IPV4 address> <Starting port> <Ending port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Initial port assignment and basic validation
    int start_port = atoi(argv[2]);
    int end_port = atoi(argv[3]);

    if (start_port < 1 || end_port > 65535 || start_port > end_port)
    {
        printf("Invalid port range\n");
        return EXIT_FAILURE;
    }

    // Populate sockaddr_in with user-defined IPv4 address
    struct sockaddr_in target_addr;
    target_addr.sin_family = AF_INET;
    if (buildIP(argv[1], &target_addr) == -1)
    {
        perror("Unable to resolve IP address");
        return EXIT_FAILURE;
    }

    printf("Starting scan on %s from port %d to %d\n", argv[1], start_port, end_port);

    startScan(target_addr, start_port, end_port);

    printf("Scan complete ;)\n");
    return EXIT_SUCCESS;
}