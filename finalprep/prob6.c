#include<unistd.h>
#include<fcntl.h>
int main(int argc, char *argv[]) {
	if (argc < 4)
		return 1;
	int fd0 = open(argv[1], O_RDONLY);
	if (fd0 == -1)
		return 1;
	int fd1 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd1 == -1) {
		close(fd1);
		return 1;
	}
	int i, arr[2], fd = fd0;
	for (i = 2; i < argc - 2; i++) {
		if (pipe(arr) == -1) {
			close(fd0), close(fd1);
			return 1;
		}
		int f = fork();
		if (f == -1) {
			close(arr[0]), close(arr[1]);
			close(fd0), close(fd1);
			return 1;
		}
		if (!f) {
			if (dup2(fd, 0) == -1) {
				close(fd);
				return 1;
			}
			close(fd), close(arr[0]);
			if (dup2(arr[1], 1) == -1) {
				close(arr[1]);
				return 1;
			}
			close(arr[1]);
			execlp(argv[i], argv[i], NULL);
			return 1;
		}
		close(fd), close(arr[1]);
		fd = arr[0];
	}
	int f = fork();
	if (f == -1) {
		close(fd0), close(fd1);
		return 1;
	}
	if (!f) {
		if (dup2(fd, 0) == -1) {
			close(fd);
			return 1;
		}
		close(fd);
		if (dup2(fd1, 1) == -1) {
			close(fd1);
			return 1;
		}
		close(fd1);
		execlp(argv[argc - 2], argv[argc - 2], NULL);
		return 1;
	}
	for (i = 2; i < argc - 2; i++)
		wait(NULL);
	return 0;
}
