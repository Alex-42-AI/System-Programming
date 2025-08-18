#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/mman.h>
#include<signal.h>
#include<stdio.h>
volatile sig_atomic_t run = 1;
void func(int sig_val) {
    if (sig_val == SIGALRM) {
        run = 0;
    }
}
int main() {
    int md = shm_open("/prob3", O_CREAT | O_EXCL | O_RDWR, 0644);
    if (md == -1)
        return 1;
    signal(SIGALRM, func);
    ftruncate(md, sizeof(int));
    int *addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, md, 0);
    *addr = 0;
    int f = fork();
    if (f == -1) {
        close(md);
        shm_unlink("/prob3");
        return 1;
    }
    alarm(5);
    if (f) {
        while (run)
            (*addr)++;
        printf("parent: %d\n", *addr);
    }
    else {
        while (run)
            (*addr)--;
        printf("child: %d\n", *addr);
    }
    munmap(addr, sizeof(int));
    close(md);
    if (f)
        shm_unlink("/prob3");
    return 0;
}