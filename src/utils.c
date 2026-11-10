#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "utils.h"

// Check if the input is a valid IPV4 address
int isValidIP(const char *ip)
{
    int result = inet_pton(AF_INET, ip, &(struct in_addr){0}) > 0;
    if (result != 1)
    {
        printf("Invalid IP Address: %s \nPlease enter a valid IP Address\n", ip);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Valid IP Address: %s\n", ip);
    }

    return result;
}
