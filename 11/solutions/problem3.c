#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<semaphore.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    int fd = open(argv[1], O_CREAT | O_WRONLY);
    if (fd == -1)
        return 1;
    sem_t *s = sem_open("/prob4", O_CREAT | O_EXCL, 0644, 1);
    if (s == SEM_FAILED) {
        close(fd);
        return 1;
    }
    int f = fork();
    if (f == -1) {
        close(fd);
        sem_close(s);
        sem_unlink("/prob4");
        return 1;
    }
    if (f) {
        int i;
        for (i = 0; i < 5; i++) {
            sem_wait(s);
            lseek(fd, 0, 2);
            write(fd, "parent\n", 7);
            sem_post(s);
        }
    }
    else {
        int i;
        for (i = 0; i < 3; i++) {
            sem_wait(s);
            lseek(fd, 0, 2);
            write(fd, "child\n", 6);
            sem_post(s);
        }
    }
    close(fd);
    sem_close(s);
    sem_unlink("/prob4");
    return 0;

}
