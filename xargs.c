#include <unistd.h>
#ifndef NARGS
#define NARGS 4
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int
main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Ingrese programa ");
		return 1;
	}
	char *line = NULL;

	size_t len = 0;
	while(getline(&line, &len, stdin) != -1 ) {
		int pid = fork();
		if (pid == 0) {
			char *args[] = {argv[1],line};
			execvp(args[0], args);

		} else {
			int status;
			wait(&status);
		}
	}

	free(line);
	return 0;
}
