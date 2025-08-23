#include<mqueue.h>
#include<unistd.h>
#include<fcntl.h>
#include"problem6.h"
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    int fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT);
    if (fd == -1)
        return 1;
    struct mq_attr mq = {.mq_maxmsg = 10, .mq_msgsize = 1};
    int q = mq_open(Q_NAME, O_RDONLY, 0, &mq);
    if (q == -1) {
        close(fd);
        return 1;
    }
    while (1) {
        char buf[1];
        int r = mq_receive(q, buf, 1, NULL);
        if (!r || r == -1)
            break;
        write(fd, buf, 1);
        if (buf[0] == '\0')
            break;
    }
    close(fd);
    mq_close(q);
    mq_unlink(Q_NAME);
    return 0;
}
