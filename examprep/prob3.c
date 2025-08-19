#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<stdio.h>
int main(int argc, char *argv[]) {
	if (argc < 5)
		return 1;
	int f = fork();
	if (f == -1)
		return 1;
	if (!f) {
		char *command = argv[1];
		int fd0 = open(argv[argc - 3], O_RDONLY);
		if (fd0 == -1)
			return 1;
		int fd1 = open(argv[argc - 2], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd1 == -1) {
			close(fd0);
			return 1;
		}
		int fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd2 == -1) {
			close(fd0);
			close(fd1);
			return 1;
		}
		dup2(fd0, 0);
		dup2(fd1, 1);
		dup2(fd2, 2);
		int i;
		for (i = 0; i < argc - 3; i++)
			argv[i] = argv[i + 1];
		argv[argc - 3] = argv[argc - 2] = argv[argc - 1] = NULL;
		execvp(command, argv);
		close(fd0), close(fd1), close(fd2);
	}
	else {
		int status;
		int w = waitpid(f, &status, 0);
		printf("%d\n", status);
	}
	return 0;
}
