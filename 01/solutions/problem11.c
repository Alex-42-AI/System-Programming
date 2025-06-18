#include<fcntl.h>
#include<string.h>
int main(int argc, char *argv[]) {
    if (argc < 3)
        return -1;
    int fd = open(argv[2], O_RDONLY);
    if (fd == -1)
        return -1;
    char *text = argv[1];
    char line[80];
    int i = 0;
    while (1) {
        char buf[1];
        int r = read(fd, buf, 1);
        if (!r || r == -1)
            break;
        i++;
        char s = buf[0];
        if (s == '\n' || i == 80) {
            if (!strstr(line, text)) {
                close(fd);
                return 0;
            }
            i = 0;
            char line[80];
        }
        else {
            line[i] = s;
        }
    }
    close(fd);
    return 1;
}