#include <stdio.h>
#include <signal.h>

void handler(int signum) {
    printf("Holanda\n");
}

int main(){
    
    void (*sighandler_t)(int);
    sighandler_t = signal(SIGTSTP,handler);

    raise(SIGTSTP); // usar comando fg en la shell. (kill -CONT)
    printf("chau\n");

    return 0;
}