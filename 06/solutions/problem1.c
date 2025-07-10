#include<stdio.h>
#include<unistd.h>
int main(int argc, char *argv[]) {
    int arr[2];
    if (pipe(arr) == -1)
        return 1;
    close(arr[1]);
    char buf[10];
    int read_res = read(arr[0], buf, 10);
    printf("%d\n", read_res);
    write(1, buf, read_res);
    close(arr[0]);
    return 0;
}