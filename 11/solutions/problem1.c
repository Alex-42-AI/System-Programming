#include<semaphore.h>
#include<fcntl.h>
#include<stdio.h>
int main() {
    sem_t *s = sem_open("/prob1", O_CREAT | O_EXCL, 0644, 7);
    if (s == SEM_FAILED)
        return 1;
    int res;
    if (sem_getvalue(s, &res) == -1) {
        sem_close(s);
        sem_unlink("/prob1");
        return 1;
    }
    printf("%d\n", res);
    sem_close(s);
    sem_unlink("/prob1");
    return 0;

}
