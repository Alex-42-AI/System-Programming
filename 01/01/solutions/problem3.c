#include <fcntl.h>
int main(int argc, char *argv[]) {
    if (argc != 3)
        return -1;
    int fd0 = open(argv[1], O_RDONLY);
    if (fd0 == -1)
        return -1;
    int fd1 = open(argv[2], O_RDONLY);
    if (fd1 == -1) {
        close(fd0);
        return -1;
    }
    while (1) {
        char buf0[1], buf1[1];
        int r0 = read(fd0, buf0, 1);
        int r1 = read(fd1, buf1, 1);
        if (r0 == -1 || r1 == -1) {
            close(fd0), close(fd1);
            return -1;
        }
        if (!r0 && !r1)
            break;
        if (!r0 || !r1) {
            close(fd0), close(fd1);
            return 1;
        }
        if (buf0[0] != buf1[0]) {
            close(fd0), close(fd1);
            return 1;
        }
    }
    close(fd0), close(fd1);
    return 0;
}