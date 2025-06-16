#include<fcntl.h>
#include<stdlib.h>
int main(int argc, char *argv[]) {
    if (argc < 3)
        return 1;
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return 1;
    int n = atoi(argv[2]), m = atoi(argv[3]), i = 1;
    if (n <= m) {
        while (1) {
            char buf[1];
            int r = read(fd, buf, 1);
            if (!r || r == -1)
                break;
            if (n <= i && i <= m)
                write(1, buf, 1);
            i++;
            if (buf[0] == '\n')
                i = 1;
        }
    }
    close(fd);
    return 0;
}