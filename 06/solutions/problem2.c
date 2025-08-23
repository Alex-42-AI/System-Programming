#include<unistd.h>
int main(int argc, char *argv[]) {
    int arr[2];
    if (pipe(arr) == -1)
        return 1;
    close(arr[0]);
    int w = write(arr[1], "test\n", 5);
    write(1, buf, w);
    close(arr[1]);
    return 0;
}
