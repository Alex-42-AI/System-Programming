#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<mqueue.h>
int main() {
    struct mq_attr mq = {.mq_maxmsg = 1, .mq_msgsize = 10};
    int q = mq_open("/unique_name", O_RDWR | O_CREAT | O_EXCL, 0644, &mq);
    if (q == -1)
        return 1;
    if (mq_send(q, "problem 2", 9, NULL) == -1) {
        mq_close(q);
        mq_unlink("/unique_name");
        return 1;
    }
    while (1) {
        char buf[1];
        int m = mq_receive(q, buf, 1, NULL);
        if (!m || m == -1)
            break;
        write(1, buf, 1);
    }
    mq_close(q);
    mq_unlink("/unique_name");
    return 0;

}
