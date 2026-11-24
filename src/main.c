#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "scanner.h"
#include "utils.h"
#include "threads.h"

/*
argv[0] -> Program Name
argv[1] -> IP Address
argv[2] -> Starting port
argv[3] -> Ending port
*/

int main(int argc, char const *argv[])
{

    // Case of invalid usage
    if (argc != 4)
    {
        printf("Usage: %s <IPV4 address> <Starting port> <Ending port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Initial port assignment and basic validation
    int start_port = strtol(argv[2], NULL, 10);
    int end_port = strtol(argv[3], NULL, 10);

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

    return EXIT_SUCCESS;
}