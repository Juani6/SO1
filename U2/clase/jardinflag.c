#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define X 2000
int num = 0;
int flag = 0; // Si flag es 1 es por que esta ocupado

void *inc(void* ptr) {
  for(int i = 0; i < X/2; i++) {
    // lock
    while(flag) {;}
    // Nada impide que aca se haga un cambio de contexto
    flag = 1; // La asignacion tampocoes atomica
    num++; // Esta operacion no es atomica
  }
  // unlock 
  flag = 0;
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
  pthread_create(&t1,NULL,inc,NULL);
  pthread_create(&t2,NULL,inc,NULL);
  
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  
  printf("Entraron : %d\n", num);
  
  return 0;
}