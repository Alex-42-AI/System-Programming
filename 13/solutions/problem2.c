#include<mqueue.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
int main() {
    struct mq_attr mq;
    mq.mq_maxmsg = 3;
    mq.mq_msgsize = 2;
    int q = mq_open("/prob2", O_CREAT | O_EXCL | O_RDWR, 0644, &mq);
    if (q == -1)
        return 1;
    int f = fork();
    if (f == -1) {
        mq_close(q);
        mq_unlink("/prob2");
        return 1;
    }
    if (f) {
        sleep(1);
        printf("parent\n");
        mq_send(q, "go", 2, 0);
        char buf[2];
        mq_receive(q, buf, 2, NULL);
        printf("parent\n");
        mq_close(q);
        mq_unlink("/prob2");
    }
    else {
        char buf[2];
        mq_receive(q, buf, 2, NULL);
        printf("child\n");
        mq_send(q, "go", 2, 0);
        mq_close(q);
    }
    return 0;
}