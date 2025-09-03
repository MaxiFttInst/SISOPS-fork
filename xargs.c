#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

#include "command.h"

int
main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Ingrese programa ");
		return 1;
	}
	char *line = NULL;

	char *fst_arg = argv[1];

	Command *command = command_init(fst_arg);
	size_t len = 0;

	while (getline(&line, &len, stdin) != -1) {
		line[strcspn(line, "\n")] = '\0';
		if (command_is_full(command)) {
			command_exec(command);
			command_empty(command);
		}
		command_add(command, line);
		/* command_print(command); */
	}
	if (!command_is_empty(command)) {
		command_exec(command);
	}
	command_free(command);
	free(line);
	return 0;
}
