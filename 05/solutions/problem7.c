#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
int main(int argc, char *argv[]) {
    if (argc < 3)
        return 1;
    char *file = argv[argc - 1];
    argv[argc - 1] = NULL;
    int i;
    for (i = 0; i < argc - 1; i++)
        argv[i] = argv[i + 1];
    int f = fork();
    if (f == -1)
        return 1;
    if (!f) {
        int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd == -1)
            return 1;
        dup2(fd, 1);
        execvp(argv[0], argv);
        close(fd);
    }
    else {
        int status;
        int w = wait(&status);
        printf("%d %d\n", w, status);
    }
    return 0;
}