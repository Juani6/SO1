#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>


void characterAtTime(char* str) {
  
  setbuf(stdout, NULL); /*Para que no bufferee*/
  char *ptr;
  int c;
  for(ptr = str; (c = *ptr++) != 0;) 
    putc(c,stdout);
  // putc castea su primer parametro a unsigned char
}

int main() {
  
  //while (1)
  //{
    
  pid_t pid = fork();
  if (pid == 0) {
    characterAtTime("output from child\n");
  } else {
    characterAtTime("output from parent\n");
  }

//  }
  

  return 0;
}

