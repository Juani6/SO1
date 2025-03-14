#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024



char* concatenar(char* str1, char* str2) {
    int len1 = strlen(str1);
    int len = (len1 + strlen(str2)) - 1;
    char* res = malloc(sizeof(char) * len);
    
    for (int i = 0; i < len; i++) {
        if (i < len1)
            res[i] = str1[i];
        else
            res[i] = str2[i - len1];
    }
    return res;
}



int main() {
    char buff[MAX], *token;
    char* tokensArr[MAX];
    int status;
    int cerrar = 0;
    const char* exitcmd = "exit";

    fgets(buff,MAX,stdin);
    
    while(cerrar == 0) {
        
        if (strcmp(buff,exitcmd) == 0)
            cerrar = 1;
        

        __pid_t pid = fork();
        if (pid == 0) {
            buff[strlen(buff)-1] = '\0';

            int i = 0;
            for(token = strtok(buff," "); token != NULL; i++) {
                tokensArr[i] = token;
                token = strtok(NULL," ");
            }
            tokensArr[i] = NULL;

            int error = execv(tokensArr[0], tokensArr);
            
            if (error == -1) {
                printf("\nError\n");
                exit(0);
            }              
        }
        else {
            wait(&status);
            fgets(buff,MAX,stdin);
            printf("Buffer : %s\n", buff);

            if (strcmp(buff,exitcmd) == 0) {
                cerrar = 1;
            }
        }
    }
    return 0;
}