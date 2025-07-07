#include<sys/stat.h>
#include<unistd.h>
int main(int argc, char *argv[]) {
    int i;
    for (i = 1; i < argc; i++) {
        struct stat st;
        if(stat(argv[i], &st) == -1)
            continue;
        chmod(argv[i], (st.st_mode & 00776) | 00040);
    }
    return 0;
}