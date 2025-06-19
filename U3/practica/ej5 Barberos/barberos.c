/*
Una barberıa tiene una sala de espera con N sillas y
un barbero. 

->Si no hay clientes para atender, el barbero se pone a dormir. 
->Si un cliente llega y todas las sillas estan ocupadas, se va. 
->Si el barbero esta ocupado pero hay sillas disponibles, se sienta en una y espera a ser atendido. 
-> Si el barbero esta dormido, despierta al barbero. 

El cliente y el barbero deben ejecutar concurrentemente las funciones me_cortan() y cortando() 
y al terminar los dos ejecutar
concurrentemente pagando() y me_pagan()
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define ASIENTOS 10 
#define CANTCLIENTES 15

sem_t sillasMutex, clienteDisponible, barberoDisponible, 
	  esperandoPago, pagoRecibido, listoParaCorte, corteHecho;
int sillasLibres = ASIENTOS;

void me_cortan() {
	sem_post(&listoParaCorte);
    printf("Cliente: Me están cortando el pelo.\n");
    sleep(1);
	sem_wait(&corteHecho);
}

void cortando() {
	sem_wait(&listoParaCorte);
    printf("Barbero: Cortando el pelo.\n");
    sleep(1);
	sem_post(&corteHecho);
}

void pagando() {
	sem_wait(&esperandoPago);
    printf("Cliente: Pagando el corte.\n");
    sleep(1);
	sem_wait(&pagoRecibido);
}

void me_pagan() {
	sem_post(&esperandoPago);
    printf("Barbero: Recibiendo el pago.\n");
    sleep(1);
	sem_post(&pagoRecibido);
}

void* f_barbero(void* argv) {
	while(1) {
		sem_wait(&clienteDisponible);
		sem_wait(&sillasMutex);
		sillasLibres--;
		sem_post(&barberoDisponible);
		sem_post(&sillasMutex);
		cortando();
		me_pagan();
	}

	return NULL;
}

void* f_cliente(void* argv) {
	while(1) {
		sem_wait(&sillasMutex);
		if (sillasLibres > 0) {
			sillasLibres--; // Descontamos una silla
			sem_post(&sillasMutex);
			sem_post(&clienteDisponible);
			sem_wait(&barberoDisponible);
			me_cortan();
			pagando();
		}
		else {
			sem_post(&sillasMutex); // Si esta ocupado liberamos las sillas
		}
	}
	return NULL;
}

int main() {
	srand(time(NULL));
	/*
	sem_t sillasMutex, clienteDisponible, barberoDisponible, 
	  pagoHecho, pagoRecibido, corteListo, CorteHecho;
	*/

	sem_init(&sillasMutex,0,1); // 1 indica que hay sillas disponibles
	sem_init(&barberoDisponible,0,0); // Inicialmente el barbero duerme
	sem_init(&clienteDisponible,0,0); // No hay clientes
	sem_init(&esperandoPago,0,0); 
	sem_init(&pagoRecibido,0,0); // No se recibio el pago
	sem_init(&listoParaCorte,0,0); // No esta listo el corte
	sem_init(&corteHecho,0,0); // No esta hecho el corte

	pthread_t thBarbero, thCliente[CANTCLIENTES];
	pthread_create(&thBarbero,NULL,f_barbero,NULL);
	
	for (int i = 0; i < CANTCLIENTES; i++)
		pthread_create(&thCliente[i],NULL,f_cliente,NULL);

	pthread_join(thBarbero, NULL);
	return 0;
}