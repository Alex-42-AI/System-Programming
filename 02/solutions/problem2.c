#include<fcntl.h>
#include<unistd.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    int fd0 = open(argv[1], O_WRONLY);
    if (fd0 == -1)
        return 1;
    close(1);
    int fd1 = dup(fd0);
    write(1, "test\n", 5);
    close(fd0), close(fd1);
    return 0;

}
