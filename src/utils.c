#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// Check if the input is a valid IPV4 address
int isValidIP(const char *ip)
{
    int result = inet_pton(AF_INET, ip, &(struct in_addr){0}) > 0;
    if (result != 1)
    {
        printf("Invalid IP Address: %s \nPlease enter a valid IP Address\n", ip);
    }
    else
    {
        printf("Valid IP Address: %s\n", ip);
    }

    return result;
}
