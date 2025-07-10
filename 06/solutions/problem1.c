#include<unistd.h>
int main(int argc, char *argv[]) {
    int arr[2];
    if (pipe(arr) == -1)
        return 1;
    close(arr[1]);
    char buf[10];
    int r = read(arr[0], buf, 10);
    write(1, buf, r);
    close(arr[0]);
    return 0;
}
