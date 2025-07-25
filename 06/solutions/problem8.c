#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
int main(int argc, char *argv[]) {
    if (argc < 4)
        return 1;
    int arr0[2], arr1[2];
    if (pipe(arr0) == -1)
        return 1;
    int f0 = fork();
    if (f0 == -1) {
        close(arr0[0]), close(arr0[1]);
        return 1;
    }
    if (!f0) {
        close(arr0[0]);
        if (dup2(arr0[1], 1) == -1) {
            close(arr0[1]);
            return 1;
        }
        close(arr0[1]);
        execlp(argv[1], argv[1], NULL);
        return 1;
    }
    if (pipe(arr1) == -1) {
        close(arr0[0]), close(arr0[1]);
        return 1;
    }
    int f1 = fork();
    if (f1 == -1) {
        close(arr0[0]), close(arr0[1]);
        close(arr1[0]), close(arr1[1]);
        return 1;
    }
    if (!f1) {
        close(arr0[1]);
        if (dup2(arr0[0], 0) == -1) {
            close(arr0[1]), close(arr1[0]), close(arr1[1]);
            return 1;
        }
        close(arr0[0]);
        close(arr1[0]);
        if (dup2(arr1[1], 1) == -1) {
            close(arr0[1]), close(arr1[1]);
            return 1;
        }
        close(arr1[1]);
        execlp(argv[2], argv[2], NULL);
        return 1;
    }
    close(arr0[0]);
    close(arr0[1]);
    int f2 = fork();
    if (f2 == -1) {
        close(arr1[0]), close(arr1[1]);
        return 1;
    }
    if (!f2) {
        close(arr1[1]);
        if (dup2(arr1[0], 0) == -1) {
            close(arr1[0]);
            return 1;
        }
        close(arr1[0]);
        execlp(argv[3], argv[3], NULL);
        return 1;
    }
    close(arr1[0]);
    close(arr1[1]);
    waitpid(f0, NULL, 0);
    waitpid(f1, NULL, 0);
    waitpid(f2, NULL, 0);
    return 0;
}