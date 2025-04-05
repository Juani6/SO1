#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

volatile int denom = 0;

void handler(int s) {
  printf("ouch\n");
  denom = 1;
}

int main() {
  printf("%d\n",denom);
  int r;
  signal(SIGFPE, handler);
  //r = 1 / denom;
  raise(SIGFPE);
  printf("%d\n",denom);
  printf("r = %d\n", r);
  return 0;
}