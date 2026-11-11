#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "scanner.h"
#include "utils.h"

/*
argv[0] -> IP Address
argv[1] -> Target Port
*/

int main(int argc, char const *argv[])
{

    if (argc != 2)
    {
        printf("Usage: %s <IPV4 address>\n", argv[0]);
        return 0;
    }

    // Populate sockaddr_in with user-defined params (port is assigned in scanPort())
    struct sockaddr_in target_addr;
    target_addr.sin_family = AF_INET;

    if (buildIP(argv[0], &target_addr) == -1)
    {
        perror("Unable to resolve IP address");
        return -1; 
    }

    scanPort(target_addr, atoi(argv[1]));

    // Temp return val
    return 0;
}