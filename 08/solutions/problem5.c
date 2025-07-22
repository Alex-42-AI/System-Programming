#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
unsigned long int count = 0;
void f0(int sig_val) {
    if (sig_val == SIGALRM) {
        printf("%ld\n", count);
        alarm(1);
    }
}
void f1(int sig_val) {
    if (sig_val == SIGINT)
        count = 0;
}
int main() {
    int i;
    alarm(1);
    for (i = 0; i < 10000000; i++) {
        count++;
        signal(SIGALRM, f0);
        signal(SIGINT, f1);
    }
    return 0;
}