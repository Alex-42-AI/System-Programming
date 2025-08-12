#include<sys/mman.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
int main() {
    int md = shm_open("/prob2", O_CREAT | O_EXCL | O_RDWR, 0644);
    if (md == -1)
        return 1;
    if (ftruncate(md, 8) == -1) {
        close(md);
        shm_unlink("/prob2");
        return 1;
    }
    char *addr = mmap(NULL, 8, PROT_READ | PROT_WRITE, MAP_SHARED, md, 0);
    if (addr == MAP_FAILED) {
        close(md);
        shm_unlink("/prob2");
        return 1;
    }
    strcpy(addr, "alphabet");
    close(md);
    if (munmap(addr, 8) == -1) {
        shm_unlink("/prob2");
        return 1;
    }
    return 0;
}


