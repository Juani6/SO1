#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "readlock.h"

#define LEC 5
#define ESC 5
#define ARRLEN 10240


int arr[ARRLEN];

void* escritor(void* arg) {
  int i;
  int num = arg - (void*)0;
  while (1) {
    sleep(random() % 3);
    printf("Escritor %d escribiendo\n", num);
    
    if (readlock_write())
      perror("ERROR READLOCK WRITE");
    
    for (i = 0; i < ARRLEN; i++) 
      arr[i] = num;
    
    if (readlock_stopWrite())
      perror("ERROR READLOCK WRITE");

  }
  return NULL;
}

void* lector(void* arg) {
  int v, i;
  int num = arg - (void*) 0;

  while (1) {
    sleep(random() % 3);
    
    if (readlock_read())
      perror("ERROR READLOCK READ");
    
      v = arr[0];
    for(i = 1; i < ARRLEN && arr[i] != v; i++);
    
    if (readlock_stopRead())
      perror("ERROR READLOCK READ");
    
      if (i > ARRLEN)
        printf("Lector %d, error de lectura\n",num);
      else
        printf("Lector %d, dato, %d\n",num,v);
  }
  return NULL;
}

int main() {
  pthread_t lectores[LEC], escritores[ESC];
  int i;
  if (readlock_init())
    perror("INIT");

  for (i = 0; i < LEC; i++) 
    pthread_create(&lectores[i],NULL,lector, i + (void*) 0);

  for (i = 0; i < ESC; i++) 
    pthread_create(&escritores[i],NULL,escritor, i + (void*) 0);

  pthread_join(lectores[0],NULL);
  
  if (readlock_destroy())
    perror("DESTROY");
  
  return 0;  
}
