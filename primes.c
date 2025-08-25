#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("ingrese numero \n");
		return 1;
	}

	int target = atoi(argv[1]);

	int num = 2;


	printf("primo %d \n", num);
	int fd[2];

	if (pipe(fd) == -1) return -1;

	int pid = fork();

	if (pid == -1) return -1;

	if (pid == 0){
		close(fd[1]);
		read(fd[0], &num, sizeof(num));
		printf("primo %d \n", num);
		int value = -1;
		while (read(fd[0], &value, sizeof(value)) != 0) {
			if(value % num != 0){

			}
		}
	} else {
		close(fd[0]);
		int i = 3;
		while (i < target) {
			if (i % num != 0){
				write(fd[1], &i, sizeof(i));
			}
			i++;
		}
		close(fd[1]);
		int status;
		wait(&status);
	}


	return 0;
}
