#include<unistd.h>
#include<sys/stat.h>
#include<sys/wait.h>
int main(int argc, char *argv[]) {
	  int i, arr[2], fd = 0;
	  for (i = 1; i < argc - 1; i++) {
		    if (pipe(arr) == -1)
			      return 1;
		    int f = fork();
		    if (f == -1) {
			      close(arr[0]), close(arr[1]);
			      return 1;
		    }
		    if (!f) {
			      if (fd) {
				        if (dup2(fd, 0) == -1) {
					          close(fd);
					          return 1;
				        }
				        close(fd);
			      }
			      close(arr[0]);
			      if (dup2(arr[1], 1) == -1) {
				        close(arr[1]);
				        return 1;
			      }
			      close(arr[1]);
			      execlp(argv[i], argv[i], NULL);
			      return 1;
		    }
		    if (fd)
			      close(fd);
		    close(arr[1]);
		    fd = arr[0];
	  }
	if (argc > 1) {
		  int f = fork();
		  if (f == -1)
			    return 1;
		  if (!f) {
			    if (fd) {
				      if (dup2(fd, 0) == -1) {
					        close(fd);
					        return 1;
				      }
				      close(fd);
			    }
			    execlp(argv[argc - 1], argv[argc - 1], NULL);
			    return 1;
		  }
		  if (fd)
			    close(fd);
	}
	for (i = 1; i < argc; i++)
		  wait(NULL);
	return 0;
}
