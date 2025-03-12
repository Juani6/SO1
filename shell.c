#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define MAX 1024


int main() {
    int status;
    while(1) {

        char buff[MAX],*token;
        fgets(buff,MAX,stdin);
        token = strtok(buff," "); 
        
        __pid_t pid = fork();
        if (pid == 0) {
            execl(arg[0],arg[0],arg[1]);
        }
        wait(&status);

    }
    return 0;
}