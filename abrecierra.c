#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define TAM 1024

int main() {
    char buff[TAM];
    int fd = open("./texto", O_RDONLY);
    int num_read = read(fd,buff,TAM/2);
    printf("%d",num_read);
    buff[num_read] = '\0';
    printf("\n%s",buff);
    return 0;
}