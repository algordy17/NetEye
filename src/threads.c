#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "scanner.h"

/*
 Using mutex to keep terminal output organized, only one terminal output will be
*/
pthread_mutex_t print_lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct
{
    struct sockaddr_in target_addr;
    int port;
} ThreadArgs;

void *scanWorker(void *arg)
{
    // Pass the void pointer back to the struct
    ThreadArgs *args = (ThreadArgs *)arg;

    // Execute the port scan
    int is_open = scanPort(args->target_addr, args->port);

    // Terminal output if open port is found
    if (is_open == 1)
    {
        // Lock the terminal output when an open port is found, only unlock when terminal output is complete
        pthread_mutex_lock(&print_lock);
        printf("**Port %d is open\n", args->port);
        pthread_mutex_unlock(&print_lock);
    }
    free(args);
    return NULL;
}

void startScan(struct sockaddr_in target_addr, int start_port, int end_port)
{
    // Threads will spawn to work through a small batch of ports before moving to the next batch
    pthread_t threads[200];

    int current_port = start_port;
    while (current_port <= end_port)
    {
        int thread_count = 0;

        // Start up to 200 threads, break when batch is finished
        for (int i = 0; i < 200 && current_port <= end_port; i++)
        {
            ThreadArgs *args = malloc(sizeof(ThreadArgs));
            args->target_addr = target_addr;
            args->port = current_port;

            pthread_create(&threads[i], NULL, scanWorker, args);
            current_port++;
            thread_count++;
        }
        // When all threads are finished with the current batch, join all threads to prepare for next batch
        for (int i = 0; i < thread_count; i++)
        {
            pthread_join(threads[i], NULL);
        }
    }
}