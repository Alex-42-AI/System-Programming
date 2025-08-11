#include<sys/mman.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main() {
    int md = shm_open("/prob1", O_CREAT | O_EXCL | O_RDWR, 0777);
    if (md == -1)
        return 1;
    ftruncate(md, 8);
    char *addr = mmap(NULL, 8, PROT_READ | PROT_WRITE, MAP_PRIVATE, md, 0);
    strcpy(addr, "alphabet");
    printf("%s\n", addr);
    close(md);
    shm_unlink("/prob1");
    return 0;
}