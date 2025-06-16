#include <fcntl.h>
#include<stdlib.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    int fd = open(argv[1], O_RDONLY), n = 10;
    if (fd == -1)
        return 1;
    if (argc > 2)
        n = atoi(argv[2]);
    int len = 0, fd0 = dup(fd);
    while (1) {
        char buf[1];
        int r = read(fd0, buf, 1);
        if (!r || r == -1)
            break;
        len += (buf[0] == '\n');
    }
    close(fd0);
    int lines = 0;
    while (1) {
        char buf[1];
        int r = read(fd, buf, 1);
        if (!r || r == -1)
            break;
        char s = buf[0];
        lines += (buf[0] == '\n');
        if (lines + n >= len)
            write(1, "%c", s);
    }
    close(fd);
    return 0;
}