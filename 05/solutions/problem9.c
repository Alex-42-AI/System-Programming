#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
int main(int argc, char *argv[]) {
    if (argc < 5)
        return 1;
    char *file0 = argv[argc - 3], *file1 = argv[argc - 2], *file2 = argv[argc - 1];
    argv[argc - 3] = argv[argc - 2] = argv[argc - 1] = NULL;
    int i;
    for (i = 0; i < argc - 1; i++)
        argv[i] = argv[i + 1];
    int f = fork();
    if (f == -1)
        return 1;
    if (!f) {
        int fd0 = open(file0, O_RDONLY);
        if (fd0 == -1)
            return 1;
        int fd1 = open(file1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd1 == -1) {
            close(fd0);
            return 1;
        }
        int fd2 = open(file2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd2 == -1) {
            close(fd0), close(fd1);
            return 1;
        }
        if (dup2(fd0, 0) == -1) {
            close(fd0), close(fd1), close(fd2);
            return 1;
        }
        close(fd0);
        if (dup2(fd1, 1) == -1) {
            close(fd1), close(fd2);
            return 1;
        }
        close(fd1);
        if (dup2(fd2, 2) == -1) {
            close(fd2);
            return 1;
        }
        close(fd2);
        execvp(argv[0], argv);
        return 1;
    }
    else {
        int status;
        int w = wait(&status);
        printf("%d %d\n", w, status);
    }
    return 0;
}

