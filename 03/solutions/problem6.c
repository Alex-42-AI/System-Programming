#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
int main() {
    if (mkdir("prob6_dir", 0755) == -1)
        return 1;
    symlink("prob6_dir/prob6_f", "new_name");
    if (unlink("new_name") == -1)
        return 1;
    return rmdir("prob6_dir") == -1;
}