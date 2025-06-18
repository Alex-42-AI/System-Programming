#include<fcntl.h>
int main(int argc, char *argv[]) {
    int i;
    for (i = 1; i < argc; i++) {
        int fd = open(argv[i], O_CREAT | O_EXCL | O_WRONLY, 0644);
        if (fd == -1)
            continue;
        while (1) {
            char buf[1];
            int r = read(0, buf, 1);
            if (!r || r == -1)
                break;
            write(fd, buf, 1);
            write(1, buf, 1);
        }
        close(fd);
    }
}