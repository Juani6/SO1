#include <unistd.h>
#include <stdio.h>

int main() {
    __pid_t pid1 = fork();
    __pid_t pid2 = fork();
    printf("pid1: %d \npid2: %d\n", pid1,pid2);
    return 0;
}