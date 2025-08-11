#include<sys/mman.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
int main() {
    int md = shm_open("/prob2", O_CREAT | O_EXCL | O_RDWR, 0777);
    if (md == -1)
        return 1;
    ftruncate(md, 8);
    char *addr = mmap(NULL, 8, PROT_READ | PROT_WRITE, MAP_SHARED, md, 0);
    strcpy(addr, "alphabet");
    return 0;
}