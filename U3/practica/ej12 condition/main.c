#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "cond.h"

#define N 5

cond_t vcond;
pthread_mutex_t lock;
int ready = 0;

void *worker(void *arg) {
    int id = (int)(long)arg;

    pthread_mutex_lock(&lock);
    while (!ready) {
        printf("[Hilo %d] Esperando condición...\n", id);
        vcond_wait(&vcond, &lock);
    }
    printf("[Hilo %d] Despertado\n", id);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[N];

    vcond_init(&vcond);
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < N; i++)
        pthread_create(&threads[i], NULL, worker, (void*)(long)i);

    sleep(2); // Tiempo para que todos esperen
    pthread_mutex_lock(&lock);
    ready = 1;
    vcond_broadcast(&vcond); // O usar vcond_signal(&vcond); para solo uno
    pthread_mutex_unlock(&lock);

    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    vcond_destroy(&vcond);
    pthread_mutex_destroy(&lock);

    return 0;
}
