#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
int main(int argc, char *argv[]) {
    if (argc < 3)
        return 1;
    int arr[2];
    int f0, f1;
    if (pipe(arr) == -1)
        return 1;
    f0 = fork();
    if (f0 == -1) {
        close(arr[0]), close(arr[1]);
        return 1;
    }
    if (!f0) {
        close(arr[0]);
        if (dup2(arr[1], 1) == -1) {
            close(arr[1]);
            return 1;
        }
        close(arr[1]);
        execlp(argv[1], argv[1], NULL);
        return 1;
    }
    f1 = fork();
    if (f1 == -1) {
        close(arr[0]), close(arr[1]);
        return 1;
    }
    if (!f1) {
        close(arr[1]);
        if (dup2(arr[0], 0) == -1) {
            close(arr[0]);
            return 1;
        }
        close(arr[0]);
        execlp(argv[2], argv[2], NULL);
        return 1;
    }
    waitpid(f0, NULL, 0);
    waitpid(f1, NULL, 0);
    close(arr[0]), close(arr[1]);
    return 0;
}
