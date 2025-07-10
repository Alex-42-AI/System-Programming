#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
int main(int argc, char *argv[]) {
    if (argc < 4)
        return 1;
    char *file0 = argv[argc - 2], *file1 = argv[argc - 1];
    argv[argc - 2] = argv[argc - 1] = NULL;
    int i;
    for (i = 0; i < argc - 1; i++)
        argv[i] = argv[i + 1];
    int f = fork();
    if (f == -1)
        return 1;
    if (!f) {
        int fd0 = open(file0, O_CREAT | O_RDONLY, 0644);
        if (fd0 == -1)
            return 1;
        int fd1 = open(file1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd1 == -1) {
            close(fd0);
            return 1;
        }
        dup2(fd0, 0);
        dup2(fd1, 1);
        execvp(argv[0], argv);
        close(fd0), close(fd1);
    }
    else {
        int status;
        int w = wait(&status);
        printf("%d %d\n", w, status);
    }
    return 0;
}