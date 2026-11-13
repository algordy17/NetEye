#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/select.h>
#include <netinet/in.h>

int scanPort(struct sockaddr_in target_addr, int target_port)
{
    // thread-safe port assignment 
    target_addr.sin_port = htons(target_port);

    // Attempt to create a new socket and store it's FD
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd < 0)
    {
        return -1; // Socket creation failure
    }

    // Add non-blocking flag to current socket flags
    int flags = fcntl(sock_fd, F_GETFL, 0);
    fcntl(sock_fd, F_SETFL, flags | O_NONBLOCK);

    // Initiate connection
    int connect_result = connect(sock_fd, (struct sockaddr *)&target_addr, sizeof(target_addr));

    // Allow EINPROGRESS to continue and only stop on hard errors from connect()
    if (connect_result < 0 && errno != EINPROGRESS)
    {
        close(sock_fd);
        return -1; //Connection failure
    }

    // Setup the file desc. set
    fd_set write_fd;
    FD_ZERO(&write_fd);
    FD_SET(sock_fd, &write_fd);

    // 500ms timeout for tcp handshake
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 500000;

    // watch for socket state change
    int select_result = select(sock_fd + 1, NULL, &write_fd, NULL, &timeout);

    if (select_result > 0)
    {
        int socket_err = 0;
        socklen_t len = sizeof(socket_err);

        if (getsockopt(sock_fd, SOL_SOCKET, SO_ERROR, &socket_err, &len) == 0)
        {
            
            if (socket_err == 0)
            {
                close(sock_fd);
                return 1; // Connection success
            }
        }
    }

    close(sock_fd);
    return 0; //No open ports were found
}