#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int argc, char *argv[]) {
    if (argc < 3)
        return 1;
    int f0 = fork();
    if (f0) {
        int f1 = fork();
        if (f1) {
            int status0, status1;
            int w0 = wait(&status0), w1 = wait(&status1);
            printf("%s\n%d\n", w0 == f0 ? argv[1] : argv[2], w0);
            printf("%s\n%d\n", w1 == f1 ? argv[2] : argv[1], w1);
        }
        else
            execlp(argv[2], argv[2], NULL);
    }
    else
        execlp(argv[1], argv[1], NULL);
    return 0;
}