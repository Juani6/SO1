#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void INThandler(int);

int main(void) {
  signal(SIGINT,INThandler);
  while(1)
    sleep(10);
    return 0;
}

void INThandler(int sig) {
  char c;
  signal(SIGINT,INThandler);
  printf("Apretaste control-c\n Queres salir? [y/n]\n");
  c = getchar();
  if (c == 'y' || c == 'Y') {
    printf("Nos vemos puto\n");
    exit(0);
  }
  else
    signal(SIGINT, INThandler);
  getchar;
}