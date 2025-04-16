#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

volatile int x = 0, y = 0;


void *wr(void *arg) {
  x = 123;
  y = 1;
  pthread_exit(0);
}
void *rd(void *arg) {
  while (!y);
  assert(x == 123);
  pthread_exit(0);
} 


int main() {
  pthread_t t1, t2;
  pthread_create(&t1,NULL,wr,NULL);
  pthread_create(&t2,NULL,rd,NULL);
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  return 0;
}