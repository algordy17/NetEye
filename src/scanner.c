#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

int populateSocket()
{
    // Store returned file descriptor for new socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    // Socket creation failure
    if (sock_fd < 0)
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    printf("Socket successfully opened\n");

    int flags = fcntl(sock_fd, F_GETFL, 0);

    // Add non-blocking flag to current socket flags
    fcntl(sock_fd, F_SETFL, flags | O_NONBLOCK);



    return 0;
}