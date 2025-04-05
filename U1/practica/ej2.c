#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>

// a) Si se cierra el file descriptor de la salida estandar (1) ¿qu´e pasa al escribir al mismo?
// b) Si se cierra el file descriptor de la entrada est´andar (0) ¿qu´e pasa al intentar leer del mismo?

// c) Si un file descriptor se duplica con dup() ¿qu´e pasa al cerrar una de las copias?
/* 
  char buff[128] = "hola estoy funcionando en la copia\n";
  int newfd = dup(1);
  write(newfd,buff,128);
  close(newfd);
  printf("hola estoy funcionando\n");
  write(newfd,buff,128); 
*/

/* 
  __pid_t pid = fork();
  if (pid == 0) {

    printf("pid hijo: %d", getpid());
    sleep(5);
    exit(0);
  }
  else {
    wait(NULL);
    printf("pid padre: %d", getpid());
    sleep(20);
} 
    */
   /* 
   int gb = pow(2,30);
   int *lolen = malloc(sizeof(char) * gb);
   for(int i = 0; i < gb; i++) {
     lolen[i] = 't';
   }
   free(lolen); 
   */
/* 
  sleep(3);
  pid_t pid = fork();
  if (pid == 0) {
    execl("./../Clase/test","./../Clase/test",NULL);
  }
  else {
    wait(NULL);
  } */
/* 
 pid_t pid = fork();
 int fd1 = open("./fd.txt", 'r');
 if (pid == 0) {
   printf("El fd del hijo es %d\n", fd1);
   close(fd1);
   //execl("./a.out","./a.out",NULL);
 }
 else {
 //  int fd2 = open("./fd.txt", 'r');
   printf("El fd del padre es %d\n", fd1);
 }
    */
int main() {
  int exp = pow(2,30);
  int *ptr = malloc(sizeof(int) * exp);
  for(int i = 0; i < exp; i++) {
    ptr[i] = 10;
  }
  sleep(10);
  printf("wait\n");
  //free(ptr);
  return 0;
}