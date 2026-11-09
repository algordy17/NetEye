#include <stdio.h>
#include "utils.c"

// Argv[1] = Given IP Adress
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: %s <IPV4 address>\n", argv[0]);
        return 0;
    }

    isValidIP(argv[1]);
}