#include<sys/mman.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
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
    if (addr == MAP_FAILURE) {
        close(md);
        shm_unlink("/prob3");
        return 1;
    }
    *addr = 0;
    int f = fork();
    if (f == -1) {
        close(md);
        shm_unlink("/prob3");
        return 1;
    }
    if (f) {
        sleep(1);
        while (*addr < 100) {
            *addr += 1;
            printf("%d, %d\n", *addr, getpid());
            sleep(2);
        }
    }
    else {
        while (*addr < 100) {
            *addr += 1;
            printf("%d, %d\n", *addr, getpid());
            sleep(2);
        }
    }
    close(md);
    shm_unlink("/prob3");
    return munmap(addr, sizeof(int)) == -1;
}
