/*
Un canal es una primitiva que permite el envıo de un valor entre threads.
Que sea sıncrono implica que no solo el lector espera al escritor (obviamente) sino que el escritor no
avanza hasta que haya aparecido un lector. Implemente canales sıncronos con la siguiente interfaz
*/
#ifndef __CANALES_H__
#define __CANALES_H__

#include <semaphore.h>
#include <pthread.h>

#define MAXMSG 256
struct channel {
	sem_t receptor;
	sem_t emisor;
	volatile int msg;
	pthread_mutex_t mutex;
};

void channel_init(struct channel *c);

void channel_write(struct channel *c, int v);

int channel_read(struct channel *c);

#endif