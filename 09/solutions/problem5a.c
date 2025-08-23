#include<mqueue.h>
#include<unistd.h>
#include<fcntl.h>
#include"problem5.h"
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return 1;
    struct mq_attr mq = {.mq_maxmsg = 10, .mq_msgsize = 1};
    int q = mq_open(Q_NAME, O_CREAT | O_WRONLY, 0644, &mq);
    if (q == -1) {
        close(fd);
        return 1;
    }
    while (1) {
        char buf[1];
        int r = read(fd, buf, 1);
        if (!r || r == -1)
            break;
        mq_send(q, buf, 1, 0);
    }
    close(fd);
    mq_close(q);
    return 0;
}


