#include<sys/mman.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
int main() {
    int open_val = shm_open("/prob2", O_RDWR, 0777);
    if (open_val == -1)
        return 1;
    char *res = mmap(NULL, 8, PROT_READ | PROT_WRITE, MAP_SHARED, open_val, 0);
    printf("%s\n", res);
    close(open_val);
    shm_unlink("/prob2");
    return 0;
}