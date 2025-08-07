#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<mqueue.h>
int main() {
    int q = mq_open("/prob1", O_CREAT | O_RDONLY | O_EXCL, 0644, NULL);
    if (q == -1)
        return 1;
    struct mq_attr mq;
    if (mq_getattr(q, &mq) == -1) {
        mq_close(q);
        mq_unlink("/prob1");
        return 1;
    }
    printf("%d, %d, %d, %d\n", mq.mq_flags, mq.mq_maxmsg, mq.mq_msgsize, mq.mq_msgsize);
    mq_close(q);
    mq_unlink("/prob1");
    return 0;
}
