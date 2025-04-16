#include <pthread.h>
#include <assert.h>
#include <stdio.h>

int x = 0, y = 0, a = 0, b = 0;

void *foo(void* arg) {
  x = 1;
  a = y;
  //pthread_exit(0);
  return NULL;
}

void* bar(void* arg) {
  y = 1;
  b = x;
  //pthread_exit(0);
  return NULL;
}

int main() {
  
  pthread_t t0,t1;
  pthread_create(&t0,NULL,foo,NULL);
  // x = 1, y = a = b = 0
  pthread_create(&t1,NULL,bar,NULL);
  // y = 1, b = x, a = ?

  pthread_join(t0,NULL);
  pthread_join(t1,NULL);

  printf("a = %d\nb = %d\na||b = %d\n", a,b, a||b);
  assert(a||b);
  
  return 0;
}