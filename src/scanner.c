#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <bits/fcntl-linux.h>

int populateSocket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    // Socket creation failed
    if (sock < 0)
    {
        return -1;
    }

    //Add non-blocking flag to current socket flags
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);

    return 0;
}