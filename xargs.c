#include <unistd.h>
#ifndef NARGS
#define NARGS 4
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>


int
main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Ingrese programa ");
		return 1;
	}
	char *line = NULL;

	char *command = argv[1];

	size_t len = 0;

	size_t array_size = 0;
	size_t array_cap = 5;
	char ***args = malloc(sizeof(char **) * array_cap);

	for (size_t i = 0; i < array_cap; i++) {
		args[i] = malloc(sizeof(char *) * (NARGS + 1));
	}

	int arg_count = 0;
	while (getline(&line, &len, stdin) != -1) {
		if (arg_count % NARGS == 0){
			args[array_size][0] = command;
			args[array_size][NARGS] = NULL;
			array_size++;

		}
		if(array_size == array_cap -1) {
			array_cap *= 2;
			args = realloc(args, sizeof(char**) * array_cap);
		}
		char *arg = malloc(sizeof(char) * len);
		strcpy(arg, line);
		args[array_size][1 + (arg_count % 4)] = arg;
		arg_count++;
	}
	bool can_fork = true;
	size_t fork_count = 0;
	while(can_fork){
		int pid = fork();
		if (pid == 0) {
			can_fork = false;

			execvp(args[fork_count][0], args[fork_count]);

		} else {
			fork_count++;
			if(fork_count == array_size){
				can_fork = false;
			}
			wait(NULL);
		}
	}

	int counter = 0;
	for (size_t j = 0; j < array_size; j++) {
		for (size_t i = 1; i < NARGS; i++) {
			if(counter < arg_count){
				/* printf("%s", args[j][i]); */
				free(args[j][i]);
				counter++;
			}
		}
	}
	for (size_t i = 0; i < array_cap; i++) {
		free(args[i]);
	}
	free(args);
	free(line);
	return 0;
}
