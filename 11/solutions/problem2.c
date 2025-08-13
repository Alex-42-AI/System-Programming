#include<semaphore.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
int main() {
    sem_t *s = sem_open("/prob2", O_CREAT | O_EXCL, 0644, 1);
    if (!s)
        return 1;
    int f = fork();
    if (f == -1) {
        sem_close(s);
        sem_unlink("/prob2");
        return 1;
    }
    if (f) {
        sem_wait(s);
        printf("parent\n");
        sem_post(s);
    }
    else {
        sem_wait(s);
        printf("child\n");
        sem_post(s);
    }
    sem_close(s);
    sem_unlink("/prob2");
    return 0;
}