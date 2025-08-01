#include<mqueue.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include"problem6.h"
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    struct mq_attr mq;
    int q = mq_open(Q_NAME, O_RDONLY, 0644, &mq);
    if (q == -1)
        return 1;
    int fd = open(argv[1], O_WRONLY);
    if (fd == -1) {
        mq_close(q);
        return 1;
    }
    while (1) {
        char buf[1];
        int m = mq_receive(q, buf, 1, NULL);
        if (!m || m == -1)
            break;
        write(fd, buf, 1);
    }
    close(fd);
    mq_close(q);
    unlink(Q_NAME);
    return 0;
}