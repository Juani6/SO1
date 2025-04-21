#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
volatile int i = 0, res = 0; 
int arr[10] = {1,2,3,4,5,6,7,8,9,10};


void* suma(void* ptr) {
  for (;i < 10; ++i) {
    //pthread_mutex_lock(&mu);
    res += arr[i];
    //printf("RES = %d\n", res);
    //pthread_mutex_unlock(&mu);
  }
  pthread_exit(0);
}

int main() {
  pthread_t t1,t2;
  pthread_create(&t1,NULL,suma,NULL);
  pthread_create(&t2,NULL,suma,NULL);
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  printf("res final = %d\n", res);
  return 0;
}