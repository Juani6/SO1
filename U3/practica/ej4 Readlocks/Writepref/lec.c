#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "readlock.h"

#define M 5
#define N 5
#define ARRLEN 10240


int arr[ARRLEN];

void* escritor(void* arg) {
  int i;
  int num = arg - (void*)0;
  while (1) {
    sleep(random() % 3);
    printf("Escritor %d escribiendo\n", num);
    
 	readlock_write();
    
    for (i = 0; i < ARRLEN; i++) 
      arr[i] = num;
    
    readlock_stopWrite();

  }
  return NULL;
}

void* lector(void* arg) {
  int v, i;
  int num = arg - (void*) 0;

  while (1) {
    sleep(random() % 3);
    
    readlock_read();
    
      v = arr[0];
    for(i = 1; i < ARRLEN && arr[i] != v; i++);
    
    readlock_stopRead();
    
      if (i > ARRLEN)
        printf("Lector %d, error de lectura\n",num);
      else
        printf("Lector %d, dato, %d\n",num,v);
  }
  return NULL;
}

int main() {
  pthread_t lectores[M], escritores[N];
  int i;
  readlock_init();

  for (i = 0; i < M; i++) 
    pthread_create(&lectores[i],NULL,lector, i + (void*) 0);

  for (i = 0; i < N; i++) 
    pthread_create(&escritores[i],NULL,escritor, i + (void*) 0);

  pthread_join(lectores[0],NULL);
  
  readlock_destroy();
  
  return 0;  
}
