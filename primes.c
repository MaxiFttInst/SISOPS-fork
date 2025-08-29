#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
make_child(int *pipe_izq)
{
	int primo;
	if (read(pipe_izq[0], &primo, sizeof(primo)) == 0)
		return 0;
	printf("primo %d\n", primo);
	int pipe_der[2];

	if (pipe(pipe_der) == -1) {
		perror("pipe");
		return -1;
	}

	int pid = fork();

	if (pid == -1) {
		perror("fork");
		return -1;
	}

	if (pid == 0) {
		close(pipe_izq[0]);
		close(pipe_der[1]);
		make_child(pipe_der);
		close(pipe_izq[1]);
	} else {
		close(pipe_der[0]);
		int value = 0;
		while (read(pipe_izq[0], &value, sizeof(value)) != 0) {
			if (value % primo != 0) {
				write(pipe_der[1], &value, sizeof(value));
			}
		}
		close(pipe_der[1]);
		close(pipe_izq[0]);
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
		close(fd[1]);
		make_child(fd);
		close(fd[0]);
	} else {
		close(fd[0]);
		int i = 3;
		while (i <= target) {
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
