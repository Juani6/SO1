#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

void characterAtTime(char* str) {
  
  setbuf(stdout, NULL); /*Para que no bufferee*/
  char *ptr;
  int c;
  for(ptr = str; (c = *ptr++) != 0;) 
    putc(c,stdout);
  // putc castea su primer parametro a unsigned char
}



/* implementar seek_write(x,v,fd) que escribe le valor v en x*/
/* implementar seek_read(x,fd) que retorna el valor que se encuentra en x*/

void seek_write(int fd, off_t pos, const char c) {
  lseek(fd,pos,SEEK_SET);
  write(fd,&c,sizeof(char));
  return;
}

char seek_read(int fd, off_t pos) {
  char c;
  lseek(fd,pos,SEEK_SET);
  int res = read(fd, &c , sizeof(char));
  return c;
}


int main() {  
  int fd = open("./file", O_RDWR);
  
  pid_t pid = fork();
  if (pid == 0) {
    char c = seek_read(fd,13);
    printf("[CHILD] leyo : %c\n", c);
    seek_write(fd,13,'T');
    c = seek_read(fd,13);
    printf("[CHILD] escribio : T\n");

  } else {

    char c = seek_read(fd,13);
    printf("[PARENT] leyo : %c\n", c);
    seek_write(fd,13,'V');
    c = seek_read(fd,13);
    printf("[PARENT] escribio : V\n");
  }
  close(fd);
  return 0;
}

/*
Cuando se llama a read o write mueve el cabezal
  > el cabezal esta asociado al archivo <

  Hay cambio de contexto y cosas raras

*/

