#ifndef __BARRERAS_H__
#define __BARRERAS_H__

#include <semaphore.h>
#include <pthread.h>

struct barrier{
	volatile int i;
	volatile int gen;
	int cant_thr;
	sem_t sem;
	sem_t mutex;
};

typedef struct barrier barrier_t;

void barrier_init(barrier_t *b, int n);

void barrier_wait(barrier_t *);

#endif