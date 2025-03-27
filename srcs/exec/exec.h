#ifndef EXEC_H
#define EXEC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "../parser/tokenizer/tokenize.h" // or the actual path where s_token is defined

void	execute_ast(t_token *node);

#endif