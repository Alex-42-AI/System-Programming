#include<sys/types.h>
#include<sys/stat.h>
int main(int argc, char *argv[]) {
	int i;
	for (i = 1; i < argc; i++) {
		struct stat st;
		if (stat(argv[i], &st) == -1)
			continue;
		chmod(argv[i], (st.st_mode & 0776) | 0020);
	}
	return 0;
}
