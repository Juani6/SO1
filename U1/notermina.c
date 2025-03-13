#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    char *arg[] = {"./print", NULL};
    while(1) {
        __pid_t pid = fork();
        if (pid == 0) {
            execl(arg[0],arg[0],arg[1]);
        }
        sleep(1);
        puts("");

    }
    return 0;
}