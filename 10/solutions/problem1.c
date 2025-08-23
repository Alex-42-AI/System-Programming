#include<sys/mman.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
int main() {
	int md = shm_open("/prob1", O_CREAT | O_EXCL | O_RDWR, 0644);
	if (md == -1)
		return 1;
	if (ftruncate(md, 11) == -1) {
		close(md);
		shm_unlink("/prob1");
		return 1;
	}
	char *addr0 = mmap(NULL, 11, PROT_WRITE, MAP_SHARED, md, 0);
	if (addr0 == MAP_FAILED) {
		close(md);
		shm_unlink("/prob1");
		return 1;
	}
	strcpy(addr0, "hello there");
	if (munmap(addr0, 11) == -1) {
		close(md);
		shm_unlink("/prob1");
		return 1;
	}
	char *addr1 = mmap(NULL, 11, PROT_READ, MAP_SHARED, md, 0);
	if (addr1 == MAP_FAILED) {
		close(md);
		shm_unlink("/prob1");
		return 1;
	}
	printf("%s\n", addr1);
	if (munmap(addr1, 11) == -1) {
		close(md);
		shm_unlink("/prob1");
		return 1;
	}
	close(md);
	shm_unlink("/prob1");
	return 0;
}
