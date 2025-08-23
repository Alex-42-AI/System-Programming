#include<unistd.h>
int main(int argc, char *argv[]) {
	if (argc < 3)
		return 1;
	symlink(argv[1], argv[2]);
	char buf[1024];
	unsigned int r = readlink(argv[2], buf, sizeof(buf)) == -1;
	if (r == -1)
		return 1;
	write(1, buf, r);
	write(1, "\n", 1);
	return 0;
}
