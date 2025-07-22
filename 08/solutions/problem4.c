#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
unsigned long int count = 0;
void func(int sig_val) {
    if (sig_val == SIGALRM) {
        printf("%ld\n", count);
        alarm(1);
    }
}
int main() {
    alarm(1);
    while (1) {
        count++;
        signal(SIGALRM, func);
    }
    return 0;
}