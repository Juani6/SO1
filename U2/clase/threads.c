#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
/*
> pthread_create() -> Crea un hilo
> pthread_exit()   -> Finaliza la ejecucion del hilo
> pthread_join()   -> esperar un thread
> pthread_cancel() -> termina un subproceso
> exit()           -> Mata el proceso entero no solamente el subproceso
*/



void* fun(void* x) {
  printf("Parametro : %d\n", *(int*)x);
  sleep(2);
  printf("hola\n");
  pthread_exit(0);
}

int main() {
  pthread_t id; // Cada thread tiene un id (thread id)
  int v = 2;

  printf("Creating thread...\n");
  pthread_create(&id,NULL,fun,&v);
  // sleep(1); // forzamos el sleep para que el scheduler haga el cambio de contexto
  int *ptr;
  pthread_join(id,(void**) &ptr);
  printf("Valor de salida : %d\n", *(int*) ((int**) &ptr));
  /*>Cada proceso es un Hilo y cuando muere el padre todos los subprocesos (threads o hilos) mueren<*/

  printf("Main running...\n");
  return 0;
}