#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// Check if the input is a valid IPV4 address
int isValidIP(const char *ip)
{
    return inet_pton(AF_INET, ip, &(struct in_addr){0}) > 0;
}


