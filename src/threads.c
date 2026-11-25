#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "scanner.h"

#define MAX_THREADS 200 // Can scale up/down as needed here for performance

typedef struct
{
    struct sockaddr_in target_addr;
    int next_port;
    int end_port;
    pthread_mutex_t port_lock;
    pthread_mutex_t print_lock;
} ScanContext;

// Single thread's routine
void *scanWorker(void *arg)
{
    ScanContext *ctx = (ScanContext *)arg;

    while (1)
    {
        // Claim the next port
        pthread_mutex_lock(&ctx->port_lock);
        if (ctx->next_port > ctx->end_port)
        {
            pthread_mutex_unlock(&ctx->port_lock);
            break;
        }
        int port = ctx->next_port++;
        pthread_mutex_unlock(&ctx->port_lock);

        // Scan outside the lock so all threads run concurrently
        int is_open = scanPort(ctx->target_addr, port);

        if (is_open == 1)
        {
            // Lock terminal for clean print output
            pthread_mutex_lock(&ctx->print_lock);
            printf("**Port %d is open**\n", port);
            pthread_mutex_unlock(&ctx->print_lock);
        }
    }

    return NULL;
}

void startScan(struct sockaddr_in target_addr, int start_port, int end_port)
{
    ScanContext ctx;
    ctx.target_addr = target_addr;
    ctx.next_port = start_port;
    ctx.end_port = end_port;

    pthread_mutex_init(&ctx.port_lock, NULL);
    pthread_mutex_init(&ctx.print_lock, NULL);

    // Ensure we do not create more threads than ports to scan
    int total_ports = end_port - start_port + 1;
    int num_threads = total_ports < MAX_THREADS ? total_ports : MAX_THREADS;

    pthread_t threads[MAX_THREADS];
    int created = 0;

    // Thread creation
    for (int i = 0; i < num_threads; i++)
    {
        if (pthread_create(&threads[created], NULL, scanWorker, &ctx) == 0)
        {
            created++;
        }
    }
    // Wait for all active workers to finish scan
    for (int i = 0; i < created; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&ctx.port_lock);
    pthread_mutex_destroy(&ctx.print_lock);
}