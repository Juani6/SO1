/*x */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define X 2000
int num = 0;
int turno = 0;

void *inc1(void* ptr) {
  for(int i = 0; i < X/2; i++) {  
    turno = 1;
    while(turno == 2) {;}

    if (turno == 1) {
      num++;
      printf("t1 : %d\n", num);
      //unlock
      turno = 2;
    }

  }
  pthread_exit(0);
}


void *inc2(void* ptr) {
  for(int i = 0; i < X/2; i++) {
    //lock
    turno = 2;
    while(turno == 1) {;}
    if (turno == 2) {
      num++;
      printf("t2 : %d\n", num);
      //unlock
      turno = 1;
    }
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
  
  return 0;
}