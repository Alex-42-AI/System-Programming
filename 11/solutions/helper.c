#include<semaphore.h>
int main(int argc, char *argv[]) {
    int i;
    for (i = 1; i < argc; i++)
        sem_unlink(argv[i]);
    return 0;
}