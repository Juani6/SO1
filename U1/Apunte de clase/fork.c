#include <unistd.h>
#include <stdio.h>

int main() {
    __pid_t pid = fork();
    if (pid == 0) {
        printf("hola soy hijo: %d\n", pid);
        printf("mi pip es: %d\n", getpid());
    }
    else {
        printf("Hola soy hijont: %d\n", pid);
        printf("mi pip es: %d\n", getpid());
    }
    printf("hola llegue\n");
    return 0;
}