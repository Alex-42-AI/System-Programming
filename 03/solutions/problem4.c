#include<unistd.h>
int main(int argc, char *argv[]) {
    if (argc < 3)
        return 1;
    if (link(argv[1], argv[2]) == -1)
        return 1;
    return (unlink(argv[1]) == -1);
}