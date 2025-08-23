#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
int main(int argc, char *argv[]) {
	int i;
	for (i = 1; i < argc; i++) {
		int fd = open(argv[i], O_RDONLY);
		if (fd == -1)
			continue;
		struct stat st;
		int s = fstat(fd, &st);
		printf("%ld %ld %ld\n", st.st_dev, st.st_ino, st.st_nlink);
		close(fd);
	}
	return 0;
}
