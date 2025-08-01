#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<mqueue.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    struct mq_attr mq;
    int q = mq_open("/unique_name", O_CREAT | O_EXCL | O_RDWR, 0644, &mq);
    if (q == -1)
        return 1;
    int f = fork();
    if (f == -1) {
        mq_close(q);
        mq_unlink("/unique_name");
        return 1;
    }
    if (f) {
        int fd = open(argv[1], O_RDONLY);
        while (1) {
            char buf[1];
            int r = read(fd, buf, 1);
            if (!r || r == -1)
                break;
            mq_send(q, buf, 1, NULL);
        }
        close(fd);
    }
    else {
        waitpid(getppid());
        while (1) {
            char buf[1];
            int m = mq_receive(q, buf, 1, NULL);
            if (!m || m == -1)
                break;
            write(1, buf, 1);
        }
    }
    mq_close(q);
    mq_unlink("/unique_name");
    return 0;
}