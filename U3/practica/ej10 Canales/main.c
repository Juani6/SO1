#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "canales.h"

#define N_PROD 3
#define N_CONS 3
#define N_MSGS 5

struct channel canal;

void* productor(void* arg) {
    int id = (int)(size_t)arg;
    for (int i = 0; i < N_MSGS; i++) {
        int val = id * 100 + i;
        printf("[P%d] Enviando: %d\n", id, val);
        channel_write(&canal, val);
        sleep(rand() % 2);
    }
    return NULL;
}

void* consumidor(void* arg) {
    int id = (int)(size_t)arg;
    for (int i = 0; i < N_MSGS; i++) {
        int val = channel_read(&canal);
        printf("[C%d] Recibido: %d\n", id, val);
        sleep(rand() % 2);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    channel_init(&canal);

    pthread_t productores[N_PROD], consumidores[N_CONS];

    for (int i = 0; i < N_PROD; i++)
        pthread_create(&productores[i], NULL, productor, (void*)(size_t)i);

    for (int i = 0; i < N_CONS; i++)
        pthread_create(&consumidores[i], NULL, consumidor, (void*)(size_t)i);

    for (int i = 0; i < N_PROD; i++)
        pthread_join(productores[i], NULL);

    for (int i = 0; i < N_CONS; i++)
        pthread_join(consumidores[i], NULL);

    return 0;
}
