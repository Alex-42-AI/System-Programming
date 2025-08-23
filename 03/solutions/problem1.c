#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
int main(int argc, char *argv[]) {
    if (argc < 3)
        return 1;
    int fd0 = open(argv[1], O_CREAT | O_EXCL, 0777);
    if (fd0 == -1)
        return 1;
    mode_t old_mask = umask(0666);
    int fd1 = open(argv[2], O_CREAT | O_EXCL, 0777);
    if (fd1 == -1) {
        close(fd0);
        return 1;
    }
    printf("%o\n", old_mask);
    umask(old_mask);
    close(fd0), close(fd1);
    return 0;
}

