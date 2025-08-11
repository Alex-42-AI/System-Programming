#include<sys/mman.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
void swap(int array[], int a, int b) {
    if (array[a] > array[b]) {
        array[a] += array[b];
        array[b] = array[a] - array[b];
        array[a] -= array[b];
    }
}
int main() {
    int md = shm_open("/prob4", O_CREAT | O_EXCL | O_RDWR, 0777);
    if (md == -1)
        return 1;
    if (ftruncate(md, 20 * sizeof(int)) == -1) {
        close(md);
        shm_unlink("/prob4");
        return 1;
    }
    int *addr = mmap(NULL, 20 * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, md, 0);
    int f = fork();
    if (f == -1) {
        close(md);
        shm_unlink("/prob4");
        return 1;
    }
    if (f) {
        sleep(1);
        while (!waitpid(f, NULL, WNOHANG)) {
            int i;
            for (i = 0; i < 20; i++) {
                printf("%d ", addr[i]);
                printf("\n");
            }
        }
    }
    
    else {
        int i, j;
        for (i = 0; i < 20; i++)
            addr[i] = random() % 100;
        for (i = 0; i < 20; i++) {
            for (j = i + 1; j < 20; j++)
                swap(addr, i, j);
            sleep(1);
        }
    }
    close(md);
    shm_unlink("/prob4");
    return 0;
}