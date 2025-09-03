#include "command.h"

#ifndef NARGS
#define NARGS 4
#endif

struct command {
	char *items[NARGS + 2];
	int index;
};

Command *
command_init(char *fst_arg)
{
	Command *command = malloc(sizeof(Command));
	command->items[NARGS + 1] = NULL;
	command->items[0] = malloc(strlen(fst_arg) + 1);
	command->index = 1;
	strcpy(command->items[0], fst_arg);
	return command;
}
void
command_empty(Command *command)
{
	for (int i = 1; i < NARGS + 1; i++) {
		free(command->items[i]);
		command->items[i] = NULL;
	}
	command->index = 1;
}

void
command_add(Command *command, char *arg)
{
	if (command->index == NARGS + 1) {
		command_empty(command);
	}
	command->items[command->index] = malloc(strlen(arg) + 1);
	strcpy(command->items[command->index], arg);
	command->index += 1;
}

bool
command_is_full(Command *command)
{
	return (command->index == NARGS + 1);
}
bool
command_is_empty(Command *command)
{
	return (command->index == 1);
}
int
command_exec(Command *command)
{
	int pid = fork();
	if (pid == -1)
		return pid;
	if (pid == 0) {
		execvp(command->items[0], command->items);
		exit(0);
	} else {
		wait(NULL);
	}

	return 0;
}
void
command_print(Command *command)
{
	for (int i = 0; i < NARGS + 1; i++) {
		printf("%s", command->items[i]);
	}
}
void
command_free(Command *command)
{
	for (int i = 0; i < NARGS; i++) {
		free(command->items[i]);
	}
	free(command);
}
