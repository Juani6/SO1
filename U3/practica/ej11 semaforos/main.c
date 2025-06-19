#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "sem.h"

#define NUM_THREADS 10
#define MAX_CONCURRENT 3

struct _Semaforo semaforo; // estructura real
void* tarea(void* arg) {
    int id = (int)(long)arg;

    printf("Hilo %d quiere entrar a la sección crítica\n", id);
    sem1_wait(&semaforo);

    printf("Hilo %d ENTRÓ a la sección crítica\n", id);
    sleep(1); // Simula trabajo
    printf("Hilo %d SALE de la sección crítica\n", id);

    sem1_post(&semaforo);
    return NULL;
}

int main() {
    pthread_t hilos[NUM_THREADS];

    sem1_init(&semaforo, MAX_CONCURRENT);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&hilos[i], NULL, tarea, (void*)(long)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(hilos[i], NULL);
    }

    sem1_destroy(&semaforo);
    return 0;
}
