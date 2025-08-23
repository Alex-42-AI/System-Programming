#include<unistd.h>
int main(int argc, char *argv[]) {
    int arr[2];
    pipe(arr);
    char buf0[5] = "0123\n", buf1[5];
    int w = write(arr[1], buf0, 5);
    write(1, buf0, w);
    int r = read(arr[0], buf1, 5);
    write(1, buf1, r);
    close(arr[0]), close(arr[1]);
    return 0;
}
