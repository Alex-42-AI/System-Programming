#include<fcntl.h>
int main(int argc, char *argv[]) {
    if (argc < 3)
        return 1;
    int fd0 = open(argv[1], O_RDONLY);
    if (fd0 == -1)
        return 1;
    int fd1 = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd1 == -1) {
        close(fd0);
        return 1;
    }
    while (1) {
        char buf[1];
        int r = read(fd0, buf, 1);
        if (!r || r == -1)
            break;
        write(fd1, buf, 1);
    }
    close(fd0), close(fd1);
    return 0;
}