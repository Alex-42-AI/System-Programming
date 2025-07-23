#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
void func(int sig_val) {
	if (sig_val == SIGCHLD)
		printf("child\n");
}
int main() {
	signal(17, func);
	int f = fork();
	if (f == -1)
		return 1;
	if (f) {
		printf("parent...\n");
		pause();
		printf("parent\n");
	}
	else {
		printf("child...\n");
		sleep(2);
	}
	return 0;
}
