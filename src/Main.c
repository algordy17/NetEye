#include <stdio.h>
#include "utils.c"


//Argv[1] = Given IP Adress
int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Usage: %s <IPV4 address>\n", argv[0]);
        return 1;
    } else {
        if (isValidIP(argv[1])) {
            printf("Valid IPV4 address: %s\n", argv[1]);

        } else {
            printf("Invalid IPV4 address: %s\n", argv[1]);
            return -1;
        }
    }



    return 0;
}