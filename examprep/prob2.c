#include<unistd.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<stdio.h>
int main(int argc, char *argv[]) {
	if (argc < 2)
		return 1;
	int f = fork();
	if (f == -1)
		return 1;
	if (f) {
		int status;
		int w = waitpid(f, &status, 0);
		printf("%d %d\n", f, status);
	}
	else {
		int i;
		for (i = 0; i < argc - 1; i++)
			argv[i] = argv[i + 1];
		argv[argc - 1] = NULL;
		execvp(argv[1], argv);
		return 1;
	}
	return 0;
}
