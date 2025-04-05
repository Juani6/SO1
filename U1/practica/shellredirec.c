#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#define MAX 128

void redir(char** token) {
  *token = strtok(NULL," ");
  FILE* f = fopen(*token,"w");
  int fd = fileno(f);
  dup2(fd, STDOUT_FILENO);
  *token = strtok(NULL, " ");  
}
void executar(char **tokensArr) {
    char path[MAX] = "/bin/";
    strcat(path,tokensArr[0]);
            int error = execv(path, tokensArr);
            
            if (error == -1)
                exit(0);
}

int main() {
    int status;
    char buff[MAX], *token, *tokensArr[MAX];
    char path[MAX] = "/bin/";
    const char EXITCMD[] = "exit";

    while(1) {
        
        printf("~ ");
        fgets(buff,MAX,stdin);
        buff[strlen(buff)-1] = '\0';
        
        if(strcmp(buff,EXITCMD) == 0) 
            return 0;

        __pid_t pid = fork();
        if (pid == 0) {
            if (strlen(buff) == 0)
                exit(0);
            
            int i = 0;
            for(token = strtok(buff," "); token != NULL; i++) {
                if (strcmp(">", token) == 0) 
                  redir(&token);
        
                tokensArr[i] = token;
                token = strtok(NULL," ");
            }

            tokensArr[i] = NULL;
            /*
            strcat(path,tokensArr[0]);
            int error = execv(path, tokensArr);
            
            if (error == -1)
                exit(0); 
            */
            executar(tokensArr);
        }
        else {
            wait(&status);
        }
    }
    return 0;
}