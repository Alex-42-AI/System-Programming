#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    int i;
    for (i = 0; i < argc - 1; i++)
        argv[i] = argv[i + 1];
    argv[argc - 1] = NULL;
    int f = fork();
    if (f == -1)
        return 1;
    if (!f)
        execvp(argv[0], argv);
    else {
        int status;
        int w = wait(&status);
        printf("%d %d\n", w, status);
    }
    return 0;
}