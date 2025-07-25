#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    int fd = open(argv[1], O_CREAT | O_WRONLY);
    if (fd == -1)
        return 1;
    int f = fork();
    if (f == -1)
        return 1;
    if (f) {
        int i;
        char *bufs[4] = {"012", "23", "345", "56"};
        for (i = 0; i < 4; i++) {
            write(fd, bufs[i], sizeof(bufs[i]));
        }
    }
    else {
        int i;
        char *bufs[5] = {"abc", "cd", "def", "fg", "ghi"};
        for (i = 0; i < 5; i++) {
            write(fd, bufs[i], sizeof(bufs[i]));
        }
    }
    close(fd);
    return 0;
}