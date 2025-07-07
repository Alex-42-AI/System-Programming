#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        exit(1);
    int f = fork();
    if (f) {
        int status;
        int w = wait(&status);
        if (WIFEXITED(status))
            printf("%d\n", WEXITSTATUS(status));
    }
    else
        execlp(argv[1], argv[1], NULL);
    return 0;
}