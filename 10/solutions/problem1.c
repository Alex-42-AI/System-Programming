#include<sys/mman.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main() {
    int md = shm_open("/prob1", O_CREAT | O_EXCL | O_RDWR, 0644);
    if (md == -1)
        return 1;
    ftruncate(md, 11);
    char *addr0 = mmap(NULL, 11, PROT_WRITE, MAP_PRIVATE, md, 0);
    if (addr0 == MAP_FAILURE) {
        close(md);
        shm_unlink("/prob1");
        return 1;
    }
    strcpy(addr0, "hello there");
    char *addr1 = mmap(NULL, 11, PROT_WRITE, MAP_PRIVATE, md, 0);
    if (addr1 == MAP_FAILURE) {
        close(md);
        shm_unlink("/prob1");
        return 1;
    }
    printf("%s\n", addr1);
    if (munmap(addr0, 11) == -1) {
        close(md);
        shm_unlink("/prob1");
        return 1;
    }
    close(md);
    shm_unlink("/prob1");
    return munmap(addr1, 11) == -1;
}
