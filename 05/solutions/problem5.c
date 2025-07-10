#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    int fd0 = open(argv[1], O_CREAT | O_RDONLY);
    if (fd0 == -1)
        return 1;
    int fd1 = open(argv[2], O_CREAT | O_APPEND);
    if (fd1 == -1)
        return 1;
    int f = fork();
    if (f == -1) {
        close(fd0), close(fd1);
        return 1;
    }
    if (f) {
        int status;
        while (1) {
            int w = waitpid(f, &status, WNOHANG);
            if (w)
                break;
            write(fd1, "parent\n", 7);
            sleep(2);
        }
    }
    else {
        while (1) {
            char buf[1];
            int r = read(fd0, buf, 1);
            if (!r || r == -1)
                break;
            write(fd1, buf, 1);
            sleep(1);
        }
    }
    close(fd0), close(fd1);
    return 0;
}