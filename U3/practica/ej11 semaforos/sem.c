#include <stdlib.h>
#include "sem.h"

void sem1_init(Sem_t sem, int n) {
	sem->value = n;
	//pthread_mutex_init(&sem->internal_lock,NULL);
	pthread_mutex_init(&sem->lock,NULL);
	pthread_cond_init(&sem->cond,NULL); 
}

void sem1_post(Sem_t sem) {
	pthread_mutex_lock(&sem->lock);
	sem->value++;
	pthread_cond_signal(&sem->cond);
	pthread_mutex_unlock(&sem->lock);
}

void sem1_wait(Sem_t sem) {
	
	pthread_mutex_lock(&sem->lock);
	while(sem->value == 0) { 
		pthread_cond_wait(&sem->cond, &sem->lock);
	}
	sem->value--;
	pthread_mutex_unlock(&sem->lock);

}

void sem1_destroy(Sem_t sem) {
	pthread_mutex_destroy(&sem->lock);
	pthread_cond_destroy(&sem->cond);
}
