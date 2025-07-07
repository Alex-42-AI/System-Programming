#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
int main() {
    printf("%d, %d\n", getpid(), getppid());
    execlp("ps", "ps", 0);
    return 0;
}