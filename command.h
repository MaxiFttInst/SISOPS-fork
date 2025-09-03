#ifndef COMMAND_H_
#define COMMAND_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

typedef struct command Command;

Command *
command_init(char *fst_arg);

void
command_empty(Command *command);

void
command_add(Command *command, char *arg);

bool
command_is_full(Command *command);

bool
command_is_empty(Command *command);

int
command_exec(Command *command);

void
command_print(Command *command);

void
command_free(Command *command);


#endif // COMMAND_H_
