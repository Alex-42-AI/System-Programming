#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>
void func(int sig_val) {
    if (sig_val == 13)
        printf("Signal\n");
}
int main() {
    signal(13, func);
    int arr[2];
    if (pipe(arr) == -1)
        return 1;
    close(arr[0]);
    int w = write(arr[1], "tester\n", 7);
    if (w == -1)
        return 1;
    printf("%d\nbuffer\n", w);
    close(arr[1]);
    return 0;
}