#include <stdlib.h>
#include "cond.h"

void vcond_init(cond_t *vcond) {
	sem_init(&vcond->sem,0,1);
	pthread_mutex_init(&vcond->internal_lock,NULL);
	vcond->waiters = 0;
}

void vcond_signal(cond_t *vcond) {
	pthread_mutex_lock(&vcond->internal_lock);
	sem_post(&vcond->sem);
	vcond->waiters--;
	pthread_mutex_unlock(&vcond->internal_lock);
}

void vcond_wait(cond_t *vcond, pthread_mutex_t* external_lock) {
	
	pthread_mutex_lock(&vcond->internal_lock);
	vcond->waiters++;
	pthread_mutex_unlock(&vcond->internal_lock);
	
	pthread_mutex_unlock(external_lock);
	sem_wait(&vcond->sem);
	pthread_mutex_lock(external_lock);
}

void vcond_broadcast(cond_t *vcond) {
	pthread_mutex_lock(&vcond->internal_lock);
	while(vcond->waiters > 0) {
		sem_post(&vcond->sem);
		vcond->waiters--;
	}
	pthread_mutex_unlock(&vcond->internal_lock);
}

void vcond_destroy(cond_t *vcond) {
	pthread_mutex_destroy(&vcond->internal_lock);
	sem_destroy(&vcond->sem);
}