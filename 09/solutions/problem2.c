#include<fcntl.h>
#include<mqueue.h>
int main() {
    struct mq_attr mq = {.mq_maxmsg = 10, .mq_msgsize = 1};
    int q = mq_open("/prob2", O_RDWR | O_CREAT | O_EXCL, 0644, &mq);
    if (q == -1)
        return 1;
    if (mq_send(q, "problem 2", 9, 0) == -1) {
        mq_close(q);
        mq_unlink("/prob2");
        return 1;
    }
    while (1) {
        char buf[1];
        int r = mq_receive(q, buf, 1, NULL);
        if (!r || r == -1)
            break;
        write(1, buf, 1);
        if (buf[0] == '\0')
            break;
    }
    mq_close(q);
    mq_unlink("/prob2");
    return 0;
}

