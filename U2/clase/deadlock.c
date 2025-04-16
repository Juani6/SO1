/*x */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define X 2000

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
int num = 0;

void *threadA(void* ptr) {
  
    pthread_mutex_lock(&mutex1);
    sleep(1);
    pthread_mutex_lock(&mutex2);
    
    printf("hola : %d\n", num);
    pthread_mutex_unlock(&mutex2);
    //unlock
    pthread_mutex_unlock(&mutex1);
  pthread_exit(0);
}



void *threadB(void* ptr) {
  
  pthread_mutex_lock(&mutex2);
  sleep(1);
  pthread_mutex_lock(&mutex1);

  printf("hola : soy threadA\n");
  
  //unlock
  pthread_mutex_unlock(&mutex1);
  pthread_mutex_unlock(&mutex2);
  pthread_exit(0);
}

int main() {
  pthread_t t1, t2;
  pthread_create(&t1,NULL,threadA,NULL);
  pthread_create(&t2,NULL,threadB,NULL);
  //turno = 1B
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  
  printf("hola : soy threadB\n");
  pthread_mutex_destroy(&mutex2);
  pthread_mutex_destroy(&mutex1); 
  return 0;
}