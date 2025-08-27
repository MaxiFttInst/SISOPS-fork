#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
make_child(int *pipe_izq)
{
	int num;
	close(pipe_izq[1]);
	if (read(pipe_izq[0], &num, sizeof(num)) == 0)
		return 0;
	printf("primo %d \n", num);
	int pipe_der[2];

	if (pipe(pipe_der) == -1)
		return -1;

	int pid = fork();

	if (pid == -1)
		return -1;

	if (pid == 0) {
		make_child(pipe_der);
	} else {
		close(pipe_der[0]);
		int value = 0;
		while (read(pipe_izq[0], &value, sizeof(value)) != 0) {
			if (value % num != 0) {
				write(pipe_der[1], &value, sizeof(value));
			}
		}
		close(pipe_der[1]);
		int status;
		wait(&status);
	}
	return 0;
}
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

	if (pipe(fd) == -1)
		return -1;

	int pid = fork();

	if (pid == -1)
		return -1;

	if (pid == 0) {
		make_child(fd);
	} else {
		close(fd[0]);
		int i = 3;
		while (i < target) {
			if (i % num != 0) {
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
