#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#define M 50
#define N 50
#define SZ 8

/*
 * El buffer guarda punteros a enteros, los
 * productores los consiguen con malloc() y los
 * consumidores los liberan con free()
 */
int* buffer[SZ];
volatile int cant_elems;
int cont;
pthread_cond_t buff_pl, buff_npl; // puede liberar y no puede respectivamente
pthread_mutex_t buff_lock;


void enviar(int *p) {
	if (p) { 
      
    if (pthread_mutex_lock(&buff_lock))
    perror("LOCK MUTEX");  
    
    // -------------------- REGION CRITICA --------------------
    while (cant_elems == SZ) // Si el buffer esta lleno esperamos que se libere 
      pthread_cond_wait(&buff_npl, &buff_lock);
    
    buffer[cant_elems] = p;
    cant_elems++;
    pthread_cond_signal(&buff_pl);
    
    // -------------------- REGION CRITICA --------------------
    
    if (pthread_mutex_unlock(&buff_lock))
    perror("UNLOCK MUTEX");
      
  }
	return;
}

int * recibir() {
	int *ptr;
  
    if (pthread_mutex_lock(&buff_lock))
    perror("LOCK MUTEX RECIBIR");  
    
    // -------------------- REGION CRITICA --------------------
    while(cant_elems == 0) 
      pthread_cond_wait(&buff_pl,&buff_lock);
    
    cant_elems--;
    ptr = buffer[cant_elems];
    pthread_cond_signal(&buff_npl);

    // -------------------- REGION CRITICA --------------------
    
    if (pthread_mutex_unlock(&buff_lock))
    perror("UNLOCK MUTEX");
     

  return ptr;
}

void * prod_f(void *arg)
{
	int id = arg - (void*)0;
	while (cont < 100) {
		sleep(1);

		int *p = malloc(sizeof *p);
		*p = random() % 100;
		printf("Productor %d: produje %p->%d\n", id, p, *p);
		enviar(p);
    cont++;
	}
	return NULL;
}

void * cons_f(void *arg)
{
	int id = arg - (void*)0;
	while (cont < 100) {
		sleep(1);

		int *p = recibir();
		printf("Consumidor %d: obtuve %p->%d\n", id, p, *p);
		
    free(p);
	}
	return NULL;
}

int main()
{
	pthread_t productores[M], consumidores[N];
	int i;
  
  if (pthread_cond_init(&buff_pl,NULL))
    perror("COND INIT");

  if (pthread_cond_init(&buff_npl,NULL))
  perror("COND INIT");

  if (pthread_mutex_init(&buff_lock,NULL))
    perror("INIT LOCK");

	for (i = 0; i < M; i++)
		pthread_create(&productores[i], NULL, prod_f, i + (void*)0);

	for (i = 0; i < N; i++)
		pthread_create(&consumidores[i], NULL, cons_f, i + (void*)0);

  for (i = 0; i < N; i++){
    pthread_join(productores[i], NULL); /* Espera para siempre */
    pthread_join(consumidores[i], NULL);
  }
  
  pthread_mutex_destroy(&buff_lock);
  pthread_cond_destroy(&buff_pl);
  pthread_cond_destroy(&buff_npl);

	return 0;
}
