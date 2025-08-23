#include<mqueue.h>
#include<unistd.h>
#include<stdio.h>
int main() {
	struct mq_attr mq;
	mq.mq_maxmsg = 3;
	mq.mq_msgsize = 2;
	int md = mq_open("/prob2", O_CREAT | O_EXCL | O_RDWR, 0644, &mq);
	int f = fork();
	if (f == -1) {
		mq_close(md);
		mq_unlink("/prob2");
	}
	if (f) {
		sleep(1);
		printf("parent\n");
		mq_send(md, "go", 2, 0);
		char buf[2];
		mq_receive(md, buf, 2, NULL);
		printf("parent\n");
	}
	else {
		char buf[2];
		mq_receive(md, buf, 2, NULL);
		printf("child\n");
		mq_send(md, "go", 2, 0);
	}
	mq_close(md);
	if (f)
		mq_unlink("/prob2");
	return 0;
}
