#include<fcntl.h>
#include<unistd.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    int fd0 = open(argv[1], O_RDONLY);
    if (fd0 == -1)
        return 1;
    int fd1 = dup(fd0), i = 0;
    while (1) {
        char buf[1];
        int r = read((i % 2 == 1 && i > 20) ? fd0 : fd1, buf, 1);
        if (!r || r == -1)
            break;
        write(1, buf, 1);
        i++;
    }
    close(fd0), close(fd1);
    return 0;
}
