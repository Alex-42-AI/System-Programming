#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<mqueue.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    struct mq_attr mq = {.mq_maxmsg = 10, .mq_msgsize = 1};
    int q = mq_open("/prob4", O_CREAT | O_EXCL | O_RDWR, 0644, &mq);
    if (q == -1)
        return 1;
    int f = fork();
    if (f == -1) {
        mq_close(q);
        mq_unlink("/prob4");
        return 1;
    }
    if (f) {
        int fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if (fd == -1)
            return 1;
        while (1) {
            char buf[1];
            int r = mq_receive(q, buf, 1, NULL);
            if (!r || r == -1)
                break;
            write(fd, buf, 1);
            if (buf[0] == '\0')
                break;
        }
        mq_close(q), close(fd);
        mq_unlink("/prob4");
    }
    else {
        while (1) {
            char buf[1];
            int r = read(0, buf, 1);
            if (!r || r == -1)
                break;
            mq_send(q, buf, 1, 0);
        }
        mq_send(q, "\0", 0);
    }
    return 0;
}
