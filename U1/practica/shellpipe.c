#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#define MAX 128

void redir(char** token, char* div) {
  *token = strtok(NULL,div);
  FILE* f = fopen(*token,"w");
  int fd = fileno(f);
  dup2(fd, STDOUT_FILENO);
  *token = strtok(NULL, div);  
}

int execute(char **tokensArr) {
    //char path[MAX] = "/bin/";
    //strcat(path,tokensArr[0]);
    int error = execvp(tokensArr[0], tokensArr);
    
    if (error == -1) {
        printf("Error\n");
    }
    return error;
}

int parse(char* buff,char** tokensArr, char* div) {
    int i = 0;
    char* token;
    for(token = strtok(buff,div); token != NULL; i++) {
         if (strcmp(">", token) == 0) {
            redir(&token,div);
        }
            tokensArr[i] = token;
            token = strtok(NULL,div);
        }
        tokensArr[i] = NULL;
    return i;
}

void plumbing(int (*pipeArr)[2], int pipenum) {
    for (int j = 0; j < pipenum; j++) {
        close(pipeArr[j][0]);
        close(pipeArr[j][1]);
    }
}

void pipeChildManager(int (*pipeArr)[2], int pipenum, int i) {
    if (i > 0) // si i>1 pisa el STDIN con las entradas de lectura de las pipes
        dup2(pipeArr[i-1][0],STDIN_FILENO);
    if (i < pipenum) // 
        dup2(pipeArr[i][1], STDOUT_FILENO);
    plumbing(pipeArr, pipenum);
}

int main() {
    char buff[MAX], 
        *tokensArr[MAX];
    const char EXITCMD[] = "exit";
    int originalOut = dup(STDOUT_FILENO);
    
    while(1) {
        
        printf("~ ");
        fgets(buff,MAX,stdin);
        buff[strlen(buff)-1] = '\0';
        /*Parsea inicialmente por cada pipe*/
        int cantCmd = parse(buff,tokensArr,"|");
        // printf("Cantidad de comandos : %d\n",cantCmd);
        int cantPipes = cantCmd-1;
        int arrPipes[cantPipes][2];

        // Inicializamos las pipes.
        for(int i = 0; i < cantPipes; i++) {
            pipe(arrPipes[i]);
        }

        if(strcmp(buff,EXITCMD) == 0) 
            return 0;

        /*Vamos a inicializar cantCmd hijos y en cada uno las pipes que les correspondan
          Donde dependiendo de su numero modifica o no la tabla de file descriptors*/
        __pid_t pidArr[cantCmd];
        for(int i = 0; i < cantCmd; i++) {
            pid_t pid = fork();
            if (pid == 0) {
                pipeChildManager(arrPipes, cantPipes, i);
                char* argArr[MAX];
                // Parsea cada comando individualmente
                int argNum = parse(tokensArr[i],argArr, " ");
                execute(argArr);
                exit(0);
            }
            pidArr[i] = pid;
            } 

        for(int j = 0; j < cantPipes; j++) {
            close(arrPipes[j][0]);
            close(arrPipes[j][1]);
        }
        for(int i = 0; i < cantCmd; i++) {
            waitpid(pidArr[i],NULL,WUNTRACED);
        }
        printf("\n");
    }
    return 0;   
} //COLO PUTO ME LA COMO SOY TINCHO