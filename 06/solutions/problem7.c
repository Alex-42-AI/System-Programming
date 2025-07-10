#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }
    int f0 = fork();
    if (f0 == -1)
        return 1;
    if (!f0) {
        int arr[2], f;
        if (pipe(arr) == -1)
            return 1;
        f = fork();
        if (f == -1) {
            close(arr[0]), close(arr[1]);
            return 1;
        }
        if (!f) {
            close(arr[0]);
            if (dup2(arr[1], 1) == -1) {
                close(arr[1]);
                return 1;
            }
            close(arr[1]);
            execlp(argv[1], argv[1], NULL);
            return 1;
        }
        else {
            close(arr[1]);
            if (dup2(arr[0], 0) == -1) {
                close(arr[0]);
                return 1;
            }
            close(arr[0]);
            execlp(argv[2], argv[2], NULL);
            return 1;
        }
    }
    return 0;
}