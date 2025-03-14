#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#define MAX 1024


char* concatenar(char* str1, char* str2) {
    int len = (strlen(str1) + strlen(str2)) - 1;
    char* res = malloc(sizeof(char) * len);
    
    for (int i = 0; i <= len; i++) {
        if (i < strlen(str1))
            res[i] = str1[i];
        else
            res[i] = str2[i - strlen(str1)];
    }
    return res;
}

int main() {
  
  char str1[] = "hola";
  char str2[] = "tincho";

  char* concadenado = concatenar(str1,str2);
  printf("%s\n\%s\n%s",str1,str2,concadenado);

  return 0;
}