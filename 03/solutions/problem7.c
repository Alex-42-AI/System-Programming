#include<unistd.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    return chdir(argv[1]) == -1;
}