/*x */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define X 2000

// Buscamos mantener la region critica lo mas chica posible
/*
Si comentamos (1) y mantenemos (2) la region critica va a ser lo que se encuentre entre el lock y unlock
y van a funcionar de manera recurrente y adecuadamente
si comentamos (2) y mantenemos (1) la ejecucion va a ser secuencial.
*/

pthread_mutex_t mutex_num = PTHREAD_MUTEX_INITIALIZER;
int num = 0;

void *inc1(void* ptr) {

  // pthread_mutex_lock(&mutex_num);    (1)

  for(int i = 0; i < X/2; i++) {  
    pthread_mutex_lock(&mutex_num); //  (2)
    num++;
    printf("t1 : %d\n", num);
    //unlock
    pthread_mutex_unlock(&mutex_num);
  }
  pthread_exit(0);
}


void *inc2(void* ptr) {
  for(int i = 0; i < X/2; i++) {
    //lock
    
    pthread_mutex_lock(&mutex_num);

      num++;
      printf("t2 : %d\n", num);
      //unlock
      pthread_mutex_unlock(&mutex_num);
  }
  pthread_exit(0);
}


/*
t1 : (t2 analogo)
leer num = 0 (*)
add 1 num
guardar vis = 1

(*) el so mete un cambio de contexto despues de la primera lectura en thread1 y al ir al thread2
hace la modificacion de la variable y el thread inicial pisa el valor que modifica el thread2
Esto es una condicion de carrera
*/



int main() {
  pthread_t t1, t2;
  pthread_create(&t1,NULL,inc1,NULL);
  pthread_create(&t2,NULL,inc2,NULL);
  //turno = 1;
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  
  printf("Entraron : %d\n", num);
  pthread_mutex_destroy(&mutex_num); 
  return 0;
}