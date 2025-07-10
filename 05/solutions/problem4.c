#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    int fd0 = open(argv[1], O_CREAT | O_RDONLY);
    if (fd0 == -1)
        return 1;
    int fd1 = open(argv[2], O_CREAT | O_WRONLY);
    if (fd1 == -1) {
        close(fd0);
        return 1;
    }
    int f = fork();
    if (f == -1) {
        close(fd0), close(fd1);
        return 1;
    }
    if (f) {
        while (1) {
            char buf[1];
            int r = read(fd0, buf, 1);
            if (!r || r == -1)
                break;
            write(fd1, buf, 1);
            sleep(1);
        }
    }
    else {
        int i;
        char *bufs[5] = {"abc", "cd", "def", "fg", "ghi"};
        for (i = 0; i < 5; i++) {
            write(fd1, bufs[i], sizeof(bufs[i]));
            sleep(2);
        }
    }
    close(fd0), close(fd1);
    return 0;
}