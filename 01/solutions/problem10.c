#include<fcntl.h>
#include<stdio.h>
int delimeter(char s) {
    return s == ' ' || s == '\t' || s == '\n';
}
int main(int argc, char *argv[]) {
    int i, t_l = 0, t_w = 0, t_c = 0, total = 0;
    for (i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd == -1)
            continue;
        total++;
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
        t_l += l; t_w += w; t_c += c;
        printf("%d %d %d %s\n", l, w, c, argv[i]);
        close(fd);
    }
    if (total > 1)
        printf("%d %d %d total\n", t_l, t_w, t_c);
    return 0;
}