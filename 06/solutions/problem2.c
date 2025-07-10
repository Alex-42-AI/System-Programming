#include<stdio.h>
#include<unistd.h>
int main(int argc, char *argv[]) {
    int arr[2];
    if (pipe(arr) == -1)
        return 1;
    close(arr[0]);
    char buf[4] = "0000";
    int w = write(arr[1], buf, 4);
    printf("%d\n", w);
    write(1, buf, w);
    close(arr[1]);
    return 0;
}