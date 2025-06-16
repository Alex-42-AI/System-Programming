#include<fcntl.h>
#include<stdio.h>
int delimeter(char s) {
    return s == ' ' || s == '\t' || s == '\n';
}
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return 1;
    int l = 0, w = 0, c = 0;
    while (1) {
        char buf[1];
        int r = read(fd, buf, 1);
        if (!r || r == -1)
            break;
        c++;
        char s = buf[0];
        if (delimeter(s)) {
            w++;
            l += (s == '\n');
        }
    }
    printf("%d %d %d %s\n", l, w, c, argv[1]);
    return 0;
}