/*
Implementamos pthread_conds con semaforos
*/

#ifndef __COND_H__
#define __COND_H__

#include <semaphore.h>
#include <pthread.h>

typedef struct _vcond {
	pthread_mutex_t internal_lock;
	sem_t sem;
	volatile int waiters;
} cond_t;

void vcond_init(cond_t *vcond);

void vcond_signal(cond_t *vcond);

void vcond_wait(cond_t *vcond, pthread_mutex_t* external_lock);

void vcond_broadcast(cond_t *vcond);

void vcond_destroy(cond_t *vcond);

#endif