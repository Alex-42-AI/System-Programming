#include<signal.h>
#include<sys/mman.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
volatile sig_atomic_t cont = 1;
void handler(int sig_val) {
	if (sig_val == SIGALRM)
		cont = 0;
}
int main() {
	int md = shm_open("/prob3", O_CREAT | O_EXCL | O_RDWR, 0644);
	if (md == -1)
		return 1;
	if (ftruncate(md, sizeof(int)) == -1) {
		close(md);
		shm_unlink("/prob3");
		return 1;
	}
	int *addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, md, 0);
	if (addr == MAP_FAILED) {
		close(md);
		shm_unlink("/prob3");
		return 1;
	}
	signal(SIGALRM, handler);
	*addr = 0;
	int f = fork();
	if (f == -1) {
		close(md);
		shm_unlink("/prob3");
		munmap(addr, sizeof(int));
		return 1;
	}
	if (f) {
		alarm(5);
		while (cont)
			(*addr)++;
		printf("%d %d\n", getpid(), *addr);
	}
	else {
		alarm(5);
		while (cont)
			(*addr)--;
		printf("%d %d\n", getpid(), *addr);
	}
	close(md);
	if (f)
		shm_unlink("/prob3");
	return munmap(addr, sizeof(int)) == -1;
}
