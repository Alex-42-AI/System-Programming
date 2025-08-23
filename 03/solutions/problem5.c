#include<unistd.h>
int main(int argc, char *argv[]) {
    if (argc < 3)
        return 1;
    if (symlink(argv[1], argv[2]) == -1)
        return 1;
    char buf[1024];
    ssize_t len = readlink(argv[2], buf, sizeof(buf));
    if (len == -1)
        return 1;
    write(1, buf, len);
    write(1, "\n", 1);
    return 0;
}
