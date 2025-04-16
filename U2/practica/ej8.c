/*x */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define X 2000  


int num = 0;
int flag[2] = {0}; 
/*
0-> No tengo intencion de entrar
1-> Tengo intencion de entrar
*/

// 0 no se asigno al turno, 1 al molinete 1, 2 al 2.
int turno = 0;

void * proc(void *arg) {
  int i;
  int id = arg - (void*)0;
  for (i = 0; i < X; i++) {
  int c;
  /* sleep? */
  c = num;
  /* sleep? */
  sleep(0.01);
  num = c + 1;
  /* sleep? */
  }
  return NULL;
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
  pthread_create(&t1,NULL,proc,NULL);
  pthread_create(&t2,NULL,proc,NULL);
  //turno = 1;
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  
  printf("Entraron : %d\n", num);
  
  return 0;
}