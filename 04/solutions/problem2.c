#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
int main() {
    printf("pid = %d\n", getpid());
    int f = fork(), status;
    printf("f = %d\n", f);
    if (f) {
        int w = wait(&status);
        if (WIFEXITED(status))
            printf("%d\n", WEXITSTATUS(status));
        printf("status = %d, wait result = %d\n", status, w);
    }
    else
        printf("ppid = %d\n", getppid());
    return 0;
}
