#include<sys/mman.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
void swap(int arr[], int i, int j) {
    if (arr[i] > arr[j]) {
        arr[i] += arr[j];
        arr[j] = arr[i] - arr[j];
        arr[i] -= arr[j];
    }
}
void sort(int arr[]) {
    int i, j;
    for (i = 0; i < 19; i++) {
        for (j = i + 1; j < 20; j++)
            swap(arr, i, j);
        sleep(1);
    }
}
void print(int arr[]) {
    int i;
    for (i = 0; i < 20; i++)
        printf("%d ", arr[i]);
    printf("\n");
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
            print(addr);
            sleep(1);
        }
    }

    else {
        int i;
        for (i = 0; i < 20; i++)
            addr[i] = rand() % 100;
        sort(addr);
    }
    close(md);
    shm_unlink("/prob4");
    return munmap(addr, sizeof(int[20])) == -1;
}
