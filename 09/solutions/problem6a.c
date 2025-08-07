#include<mqueue.h>
#include<fcntl.h>
#include"problem6.h"
int main() {
    struct mq_attr mq = {.mq_maxmsg = 10, .mq_msgsize = 1};
    int q = mq_open(Q_NAME, O_CREAT | O_WRONLY, 0644, &mq);
    if (q == -1)
        return 1;
    while (1) {
        char buf[1];
        int r = read(0, buf, 1);
        if (!r || r == -1)
            break;
        mq_send(q, buf, 1, (unsigned)1);
    }
    mq_send(q, "\0", 1, (unsigned)1);
    mq_close(q);
    return 0;
}
