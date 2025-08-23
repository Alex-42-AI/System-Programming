#include<sys/mman.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
int main() {
	int md = shm_open("/prob2", O_CREAT | O_EXCL | O_RDWR, 0644);
	if (md == -1)
		return 1;
	if (ftruncate(md, 5) == -1) {
		close(md);
		shm_unlink("/prob2");
		return 1;
	}
	char *addr = mmap(NULL, 5, PROT_WRITE, MAP_SHARED, md, 0);
	if (addr == MAP_FAILED) {
		close(md);
		shm_unlink("/prob2");
		return 1;
	}
	strcpy(addr, "hello");
	if (munmap(addr, 5) == -1) {
		close(md);
		shm_unlink("/prob2");
		return 1;
	}
	close(md);
	return 0;
}
