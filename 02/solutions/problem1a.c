#include<fcntl.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    int fd0 = open(argv[1], O_RDONLY);
    if (fd0 == -1)
        return 1;
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1) {
        close(fd0);
        return 1;
    }
    int i = 0;
    while (1) {
        char buf[1];
        int r = read(i ? fd0 : fd1, buf, 1);
        if (!r || r == -1)
            break;
        write(1, buf, 1);
        i = !i;
    }
    close(fd0), close(fd1);
    return 0;
}
