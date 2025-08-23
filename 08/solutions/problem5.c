#include<signal.h>
#include<unistd.h>
#include<stdio.h>
long unsigned int c = 0;
void f(int sig_val) {
	if (sig_val == SIGALRM) {
		printf("%ld\n", c);
		alarm(1);
	}
	else if (sig_val == SIGINT)
		c = 0;
}
void main() {
	alarm(1);
	while (1) {
		signal(SIGALRM, f);
		signal(SIGINT, f);
		c++;
	}
}
