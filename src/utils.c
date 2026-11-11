#include <arpa/inet.h>
#include "utils.h"
#include <netinet/in.h>

// Check if the input is a valid IPV4 address
int buildIP(const char *ip, struct sockaddr_in *target)
{
    int result = inet_pton(AF_INET, ip, &(target->sin_addr));
    if (result != 1)
    {
        return -1;
    }

    return 1;
}
