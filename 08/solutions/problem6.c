#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>
void func(int sig_val) {
    if (sig_val == 15)
        printf("Terminated\n");
}
int main() {
    int f = fork();
    if (f == -1)
        return 1;
    if (f) {
        kill(0, SIGTERM);
        sleep(1);
        kill(0, SIGTERM);
    }
    else
        signal(SIGTERM, func);
    return 0;
}