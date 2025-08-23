#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
int main(int argc, char* argv[]) {
    int arr[2];
    if (pipe(arr) == -1)
        return 1;
    int f = fork();
    if (f == -1) {
        close(arr[0]), close(arr[1]);
        return 1;
    }
    if (!f) {
        while (1) {
            char buf[1];
            int r = read(arr[0], buf, 1);
            if (!r || r == -1)
                break;
            write(1, buf, r);
        }
    }
    else {
        int i, status;
        for (i = 1; i < argc; i++) {
            write(arr[1], argv[i], sizeof(argv[i]));
            sleep(1);
        }
        wait(&status);
    }
    close(arr[0]), close(arr[1]);
    return 0;
}
