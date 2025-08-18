#include<semaphore.h>
#include<sys/mman.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    int md = shm_open("/prob4", O_CREAT | O_EXCL | O_RDWR, 0644);
    if (md == -1)
        return 1;
    if (ftruncate(md, sizeof(int)) == -1) {
        close(md);
        shm_unlink("/prob4");
        return 1;
    }
    int *addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, md, 0);
    if (addr == MAP_FAILED) {
        close(md);
        shm_unlink("/prob4");
        return 1;
    }
    *addr = 0;
    sem_t *s = sem_open("/rw_mutex", O_CREAT | O_EXCL, 0644, 1);
    if (s == SEM_FAILED) {
        munmap(addr, sizeof(int));
        close(md);
        shm_unlink("/prob4");
        return 1;
    }
    sem_t *t = sem_open("/mutex", O_CREAT | O_EXCL, 0644, 1);
    if (t == SEM_FAILED) {
        munmap(addr, sizeof(int));
        close(md);
        shm_unlink("/prob4");
        sem_close(s);
        sem_unlink("/rw_mutex");
        return 1;
    }
    int f0 = fork(), f1 = -1;
    if (f0 == -1) {
        munmap(addr, sizeof(int));
        close(md);
        shm_unlink("/prob4");
        sem_close(s);
        sem_unlink("/rw_mutex");
        sem_close(t);
        sem_unlink("/mutex");
        return 1;
    }
    if (f0) {
        int i, j;
        f1 = fork();
        if (f1 == -1) {
            munmap(addr, sizeof(int));
            close(md);
            shm_unlink("/prob4");
            sem_close(s);
            sem_unlink("/rw_mutex");
            sem_close(t);
            sem_unlink("/mutex");
            return 1;
        }
        if (f1) {
            int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (fd == -1) {
                munmap(addr, sizeof(int));
                close(md);
                shm_unlink("/prob4");
                sem_close(s);
                sem_unlink("/rw_mutex");
                sem_close(t);
                sem_unlink("/mutex");
                return 1;
            }
            for (i = 0; i < 5; i++) {
                sem_wait(s);
                dprintf(fd, "parent: %d\n", i);
                sem_post(s);
            }
            close(fd);
        }
        else {
            int fd = open(argv[1], O_RDONLY);
            if (fd == -1) {
                munmap(addr, sizeof(int));
                close(md);
                shm_unlink("/prob4");
                sem_close(s);
                sem_unlink("/rw_mutex");
                sem_close(t);
                sem_unlink("/mutex");
                return 1;
            }
            for (j = 0; j < 3; j++) {
                sem_wait(t);
                if (++(*addr) == 1)
                    sem_wait(s);
                sem_post(t);
                char buf[10];
                int r = read(fd, buf, 10);
                if (r > 0)
                    printf("%s", buf);
                sem_wait(t);
                if (!(--(*addr)))
                    sem_post(s);
                sem_post(t);
            }
            close(fd);
        }
    }
    else {
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            munmap(addr, sizeof(int));
            close(md);
            shm_unlink("/prob4");
            sem_close(s);
            sem_unlink("/rw_mutex");
            sem_close(t);
            sem_unlink("/mutex");
            return 1;
        }
        int k;
        for (k = 0; k < 4; k++) {
            sem_wait(t);
            if (++(*addr) == 1)
                sem_wait(s);
            sem_post(t);
            char buf[10];
            int r = read(fd, buf, 10);
            if (r > 0)
                printf("%s", buf);
            sem_wait(t);
            if (!(--(*addr)))
                sem_post(s);
            sem_post(t);
        }
        close(fd);
    }
    sem_close(s), sem_close(t);
    if (f0 && f1) {
        munmap(addr, sizeof(int));
        sem_unlink("/rw_mutex");
        sem_unlink("/mutex");
    }
    return 0;
}