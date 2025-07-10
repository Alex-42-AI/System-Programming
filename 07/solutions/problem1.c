#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
int main(int argc, char *argv[]) {
    int i, in_fd = 0, arr[2];
    for (i = 1; i < argc; i++) {
        if (i != argc - 1) {
            if (pipe(arr) == -1)
                return 1;
        }
        int f = fork();
        if (f == -1)
            return 1;
        if (!f) {
            if (in_fd) {
                dup2(in_fd, 0);
                close(in_fd);
            }
            if (i != argc - 1) {
                close(arr[0]);
                dup2(arr[1], 1);
                close(arr[1]);
            }
            execlp(argv[i], argv[i], NULL);
            return 1;
        }
        else {
            if (in_fd)
                close(in_fd);
            if (i != argc - 1) {
                close(arr[1]);
                in_fd = arr[0];
            }
        }
    }
    for (i = 1; i < argc; i++)
        wait(NULL);
    return 0;
}