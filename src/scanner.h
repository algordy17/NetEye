#include <netinet/in.h>
#ifndef SCANNER_H
#define SCANNER_H

int scanPort(struct sockaddr_in target_addr, int target_port);

#endif