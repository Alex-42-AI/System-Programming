#include<signal.h>
#include<unistd.h>
#include<stdio.h>
void f(int sig_val) {
	if (sig_val == SIGPIPE)
		printf("Sigpipe\n");
}
int main() {
	signal(SIGPIPE, f);
	int arr[2];
	if (pipe(arr) == -1)
		return 1;
	close(arr[0]);
	write(arr[1], "test\n", 5);
	close(arr[1]);
	return 0;
}
