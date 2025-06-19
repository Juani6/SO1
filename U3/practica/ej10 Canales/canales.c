#include <stdlib.h>
#include "canales.h"

void channel_init(struct channel *c) {
	sem_init(&c->receptor,0,0);
	sem_init(&c->emisor,0,1);
	pthread_mutex_init(&c->mutex,NULL);
}

void channel_write(struct channel *c, int v) {
	sem_wait(&c->emisor);
	pthread_mutex_lock(&c->mutex);
	c->msg = v;
	pthread_mutex_unlock(&c->mutex);
	sem_post(&c->receptor);
	sem_wait(&c->emisor);
	sem_post(&c->emisor);
}

int channel_read(struct channel *c) {
	int res;
	sem_wait(&c->receptor);
	pthread_mutex_lock(&c->mutex);
	res = c->msg;
	pthread_mutex_unlock(&c->mutex);
	sem_post(&c->emisor);
	return res;
}

/*
Canal
Espera a que este el emisor disponible
Escribe
Manda senal que esta habilitado la lectura
Espera la confirmacion de lectura
una vez recibida suelta el emisor

EL lector
Espera la senal de que esta el msg disponible
Lee
Envia la confirmacion de lectura
*/