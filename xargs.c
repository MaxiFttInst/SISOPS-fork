#include <unistd.h>
#ifndef NARGS
#define NARGS 4
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	char *items[NARGS + 2];
	int index;
} Args;

Args *
args_init(char *command)
{
	Args *args = malloc(sizeof(Args));
	args->items[NARGS + 1] = NULL;
	args->items[0] = malloc(strlen(command) + 1);
	args->index = 1;
	strcpy(args->items[0], command);
	return args;
}
void
args_empty(Args *args)
{
	for (int i = 1; i < NARGS + 1; i++) {
		free(args->items[i]);
		args->items[i] = NULL;
	}
	args->index = 1;
}

void
args_add(Args *args, char *arg)
{
	if (args->index == NARGS + 1) {
		args_empty(args);
	}
	args->items[args->index] = malloc(strlen(arg) + 1);
	strcpy(args->items[args->index], arg);
	args->index += 1;
}

bool
args_is_full(Args *args)
{
	return (args->index == NARGS + 1);
}
bool
args_is_empty(Args *args)
{
	return (args->index == 1);
}
int
args_exec(Args *args)
{
	int pid = fork();
	if (pid == -1)
		return pid;
	if (pid == 0) {
		execvp(args->items[0], args->items);
		exit(0);
	} else {
		wait(NULL);
	}

	return 0;
}
void
args_print(Args *args)
{
	for (int i = 0; i < NARGS + 1; i++) {
		printf("%s", args->items[i]);
	}
}
void
args_free(Args *args)
{
	for (int i = 0; i < NARGS; i++) {
		free(args->items[i]);
	}
	free(args);
}

int
main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Ingrese programa ");
		return 1;
	}
	char *line = NULL;

	char *command = argv[1];

	Args *args = args_init(command);
	size_t len = 0;

	while (getline(&line, &len, stdin) != -1) {
		line[strcspn(line, "\n")] = '\0';
		if (args_is_full(args)) {
			args_exec(args);
			args_empty(args);
		}
		args_add(args, line);
		/* args_print(args); */
	}
	if (!args_is_empty(args)) {
		args_exec(args);
	}
	args_free(args);
	free(line);
	return 0;
}
