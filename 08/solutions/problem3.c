#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>
void func(int sig_val) {
    if (sig_val == 17)
        printf("Done\n");
    else
        printf("tf???\n");
}
int main() {
    int f = fork();
    if (f == -1)
        return 1;
    if (f) {
        signal(17, func);
        pause();
        printf("parent.\n");
    }
    else {
        printf("child...\n");
        sleep(3);
    }
    return 0;
}