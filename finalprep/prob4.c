#include<unistd.h>
#include<sys/stat.h>
#include<sys/wait.h>
int main(int argc, char *argv[]) {
	if (argc < 3)
		return 1;
	int arr[2];
	if (pipe(arr) == -1)
		return 1;
	int f = fork();
	if (f == -1) {
		close(arr[0]), close(arr[1]);
		return 1;
	}
	if (f) {
		close(arr[1]);
		if (dup2(arr[0], 0) == -1) {
			close(arr[0]);
			return 1;
		}
		close(arr[0]);
		waitpid(f, NULL, 0);
		execlp(argv[1], argv[1], NULL);
		return 1;
	}
	else {
		close(arr[0]);
		if (dup2(arr[1], 1) == -1) {
			close(arr[1]);
			return 1;
		}
		close(arr[1]);
		execlp(argv[2], argv[2], NULL);
		return 1;
	}
	return 0;
}
