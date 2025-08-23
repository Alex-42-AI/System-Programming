#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    int f = fork();
    if (f == -1)
        return 1;
    if (f) {
        int status;
        int w = wait(&status);
        if (WIFEXITED(status))
            printf("%d\n", WEXITSTATUS(status));
        return 0;
    }
    execlp(argv[1], argv[1], NULL);
    return 1;
}
