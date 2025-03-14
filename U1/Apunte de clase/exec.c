#include <unistd.h>
#include <stdio.h>

int main() {
    char *arg[] = {"./print", NULL};
    execl(arg[0], arg[0], arg[1]);

    printf("Esto no se imprime.");
    
    return 0;
}