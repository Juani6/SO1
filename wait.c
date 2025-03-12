#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    int status;

    __pid_t pid = fork();
    if (pid == 0) {
        printf("child pid: %d\n", getpid());
        sleep(2);
        printf("hijo acabado\n");
        exit(0);
    }
    else {
        wait(&status);
        printf("Hola yasta. El estado es: %d\n", status);
    }

    return 0;
}