#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
void func(int _) {}
int main() {
    signal(SIGUSR1, func);
    signal(SIGUSR2, func);
    int f = fork();
    if (f == -1)
        return 1;
    if (f) {
        sleep(1);
        printf("parent\n");
        fflush(stdout);
        kill(f, SIGUSR2);
        pause();
        printf("parent\n");
        fflush(stdout);
    }
    else {
        pause();
        printf("child\n");
        fflush(stdout);
        kill(getppid(), SIGUSR1);
    }
    return 0;
}