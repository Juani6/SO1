#include <stdlib.h>
#include <semaphore.h>
#include "barreras.h"

void barrier_init(barrier_t *b, int n) {
	b->cant_thr = n;
	b->i = 0;
	b->gen = 0;
	sem_init(&b->sem,0,0);
	sem_init(&b->mutex,0,1);
}

void barrier_wait(barrier_t *b) {
	int mi_gen;
	sem_wait(&b->mutex);
	mi_gen = b->gen;
	b->i++;
	if (b->i == b->cant_thr) {
		b->gen++;
		b->i = 0;
		for (int j = 0; j < b->cant_thr-1; j++) 
			sem_post(&b->sem);
		sem_post(&b->mutex);
	}
	else {
		sem_post(&b->mutex);
		do {
			sem_wait(&b->sem);
		} while (b->gen == mi_gen);
	}
}