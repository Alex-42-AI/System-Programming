#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
void func(int sig_val) {
	if (sig_val == SIGTERM)
		printf("SIGTERM received\n");
}
int main() {
	signal(SIGTERM, func);
	int f = fork();
	if (f == -1)
		return 1;
	if (f) {
		kill(f, SIGTERM);
		sleep(1);
		kill(f, SIGTERM);
	}
	else
		pause();
	return 0;
}
