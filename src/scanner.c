#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <poll.h>
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
        return -1; // Connection failure
    }

    struct pollfd pfd;
    pfd.fd = sock_fd;
    pfd.events = POLLOUT;
    pfd.revents = 0;

    // watch for socket state change
    int poll_result = poll(&pfd, 1, 500);

    if (poll_result > 0 && (pfd.events & POLLOUT))
    {
        int socket_err = 0;
        socklen_t len = sizeof(socket_err);

        if (getsockopt(sock_fd, SOL_SOCKET, SO_ERROR, &socket_err, &len) == 0 && socket_err == 0)
        {
            close(sock_fd);
            return 1; // Port is open
        }
    }
    close(sock_fd);
    return 0; // Port is closed/filtered
}