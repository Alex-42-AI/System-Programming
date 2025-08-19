#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
int main() {
	mkdir("prob12_dir", 0644);
	symlink("prob12_dir/prob12_file", "new_file");
	if (unlink("new_file") == -1)
		return 1;
	return rmdir("prob12_dir") == -1;
}
