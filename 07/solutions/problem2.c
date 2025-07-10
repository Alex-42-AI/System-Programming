#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
int main(int argc, char *argv[]) {
    if (argc < 3)
        return 1;
    int fd0 = open(argv[1], O_CREAT | O_RDONLY, 0644);
    if (fd0 == -1)
        return 1;
    int fd1 = open(argv[argc - 1], O_CREAT | O_WRONLY, 0666);
    if (fd1 == -1) {
        close(fd0);
        return 1;
    }
    int i, in_fd = fd0, arr[2];
    for (i = 2; i < argc - 1; i++) {
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
            if (i == argc - 1) {
                dup2(fd1, 1);
                close(fd1);
            }
            else {
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
    for (i = 1; i < argc - 2; i++)
        wait(NULL);
    close(fd1);
    return 0;
}