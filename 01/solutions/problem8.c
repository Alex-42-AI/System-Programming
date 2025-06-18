#include<fcntl.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    int fd = open(argv[1], O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (fd == -1)
        return 1;
    while (1) {
        char buf[1];
        int r = read(0, buf, 1);
        if (!r || r == -1)
            break;
        write(fd, buf, 1);
    }
    close(fd);
    return 0;
}