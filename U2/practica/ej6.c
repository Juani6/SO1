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

static inline void incl(int* ptr) {
  asm("incl %0" : "+m"(*ptr) :  : "memory");
}

static inline void incl2(int* ptr) {
  asm("lock; incl %0" : "+m"(*ptr) :  : "memory");
}

void *inc1(void* ptr) {
  for(int i = 0; i < X/2; i++) {  
    // lock
    flag[0] = 1;
    //
    turno = 2;
    asm("mfence");
    while(flag[1] == 1 && turno == 2) {;}

    num++;

    //incl(&num);

    //unlock
    flag[0] = 0;

    //incl(&num);
  }
  pthread_exit(0);
}


void *inc2(void* ptr) {
  for(int i = 0; i < X/2; i++) {
    //lock
    flag[1] = 1;
    //
    turno = 1;
    // lock
    asm("mfence");
    while(flag[0] == 1 && turno == 1);
    //incl(&num);
    num++;


    //unlock
    flag[1] = 0;
    //incl(&num);
  }
  pthread_exit(0);
}

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