#include<unistd.h>
int main() {
	int arr[2];
	if (pipe(arr) == -1)
		return 1;
	close(arr[1]);
	while (1) {
		char buf[1];
		int r = read(arr[0], buf, 1);
		if (!r || r == -1)
			break;
		write(1, buf, 1);
	}
	close(arr[0]);
	return 0;
}
