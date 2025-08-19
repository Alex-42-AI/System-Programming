#include<utime.h>
#include<sys/types.h>
int main(int argc, char *argv[]) {
	if (argc < 2)
		return 1;
	struct utimbuf buf;
	utime(argv[1], &buf);
	buf.actime -= 3600;
	buf.modtime += 60;
	return 0;
}
