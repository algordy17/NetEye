#ifndef UTILS_H
#define UTILS_H 
#include <netinet/in.h>

int buildIP(const char *ip, struct sockaddr_in *target);

#endif