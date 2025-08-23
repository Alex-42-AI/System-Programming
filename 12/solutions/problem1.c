#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
void func(int _) {}
int main() {
	signal(SIGTERM, func);
	int f = fork();
	if (f == -1)
		return 1;
	if (f) {
		sleep(1);
		printf("parent\n");
		fflush(stdout);
		kill(f, SIGTERM);
		pause();
		printf("parent\n");
		fflush(stdout);
	}
	else {
		pause();
		printf("child\n");
		fflush(stdout);
		kill(getppid(), SIGTERM);
	}
	return 0;
}
