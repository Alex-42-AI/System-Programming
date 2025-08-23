#include<sys/mman.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
int main() {
    int md = shm_open("/prob2", O_RDWR, 0);
    if (md == -1) {
        shm_unlink("/prob2");
        return 1;
    }
    char *addr = mmap(NULL, 8, PROT_READ | PROT_WRITE, MAP_SHARED, md, 0);
    if (addr == MAP_FAILED) {
        close(md);
        shm_unlink("/prob2");
        return 1;
    }
    printf("%s\n", addr);
    close(md);
    shm_unlink("/prob2");
    return munmap(addr, 8) == -1;
}#include<sys/mman.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
int main() {
	int md = shm_open("/prob2", O_RDONLY, 0);
	if (md == -1) {
		shm_unlink("/prob2");
		return 1;
	}
	char *addr = mmap(NULL, 5, PROT_READ, MAP_SHARED, md, 0);
	if (addr == MAP_FAILED) {
		close(md);
		shm_unlink("/prob2");
		return 1;
	}
	printf("%s\n", addr);
	close(md);
	shm_unlink("/prob2");
	return munmap(addr, 5) == -1;
}
