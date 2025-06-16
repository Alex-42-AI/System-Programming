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
    int lines = 0;
    while (1) {
        char buf[1];
        int r = read(fd, buf, 1);
        if (!r || r == -1)
            break;
        char s = buf[0];
        write(1, "%c", s);
        if (s == '\n') {
            lines++;
            if (lines == n)
                break;
        }
    }
    close(fd);
    return 0;
}