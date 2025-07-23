#include<signal.h>
#include<unistd.h>
int main() {
	signal(SIGPIPE, SIG_IGN);
	int arr[2];
	if (pipe(arr) == -1)
		return 1;
	close(arr[0]);
	write(arr[1], "test\n", 5);
	close(arr[1]);
	return 0;
}
