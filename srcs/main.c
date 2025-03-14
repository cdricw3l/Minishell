#include "main.h"

void execute_command(char *cmd)//cmd means 'Command'
{
    char *args[] = {cmd, NULL};//Initailizing the *args[]. args[0] = cmd, args[1] = NULL; 

    pid_t pid = fork();//create a child process

    if (pid == 0) // Child process is 0
    {
        if (execvp(cmd, args) == -1)//Replaces the child process with the given command.
            perror("minishell");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0) // Parent process
        wait(NULL);//Makes the parent wait for the child process to finish before continuing.
    else
        perror("fork");
}

int main(void)
{
    char *input;

    while (1)//infinite loop
    {
        input = readline("minishell$ ");//Possible External functs
        if (!input) // Handle Ctrl+D
        {
            printf("exit\n");
            break;
        }
        if (*input) // If not empty input
        {
            add_history(input);//Possible External functs
            execute_command(input);
        }
        free(input);
    }
    return (0);
}
