#ifndef __SEM_H__
#define __SEM_H__

#include <pthread.h>

struct _Semaforo {
	volatile int value;
	pthread_mutex_t lock; 
	pthread_cond_t cond;
};

typedef struct _Semaforo* Sem_t;

void sem1_init(Sem_t, int);

void sem1_post(Sem_t);

void sem1_wait(Sem_t);

void sem1_destroy(Sem_t);



#endif