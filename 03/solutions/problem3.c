#include<sys/stat.h>
#include<utime.h>
#include<unistd.h>
int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;
    struct stat st;
    if (stat(argv[1], &st) == -1)
        return 1;
    struct utimbuf t;
    utime(argv[1], &t);
    t.actime = st.st_atime - 3600;
    t.modtime = st.st_mtime + 60;
    return utime(argv[1], &t) == -1;
}