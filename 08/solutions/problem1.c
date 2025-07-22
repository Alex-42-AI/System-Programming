#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>
int main() {
    signal(13, SIG_IGN);
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