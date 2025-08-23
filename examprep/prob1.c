#include<unistd.h>
#include<sys/stat.h>
#include<stdio.h>
int main() {
	printf("%d %d\n", getpid(), getppid());
	execlp("ps", "ps", NULL);
	return 1;
}
