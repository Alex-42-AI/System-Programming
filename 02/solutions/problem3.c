#include<sys/stat.h>
#include<stdio.h>
#include<fcntl.h>
int main(int argc, char *argv[]) {
    int i;
    for (i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd == -1)
            continue;
        int s = fstat(fd, NULL);
        printf("%d\n", s);
        close(fd);
    }
    return 0;
}