#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

int main() {
    int status;
    char buff[MAX], *token;
    char* tokensArr[MAX];
    char path[] = "/bin/";
    const char exitcmd[] = "exit";

    printf("> ");
    fgets(buff,MAX,stdin);

    while(1) {
        buff[strlen(buff)-1] = '\0';
        
        if(strcmp(buff,exitcmd) == 0) {
            return 0;
        }

        __pid_t pid = fork();
        if (pid == 0) {
            int i = 0;
            for(token = strtok(buff," "); token != NULL; i++) {
                tokensArr[i] = token;
                token = strtok(NULL," ");
            }
            tokensArr[i] = NULL;
            
            strcat(path,tokensArr[0]);
            int error = execv(path, tokensArr);
            if (error == -1)
                exit(0);
        }
        else {
            wait(&status);
            printf("> ");
            fgets(buff,MAX,stdin);
        }
    }
    return 0;
}