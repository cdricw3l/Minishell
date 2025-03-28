#include "../../include/main.h"

// Function to execute AST recursively
void execute_ast(t_token *node)
{
    if (!node)
        return;

    // If it's a command (leaf node)
    if (node->token == 1) // Assuming 1 is CMD type
    {
        pid_t pid = fork();
        if (pid == 0) // Child process
        {
            char *args[] = {"/bin/sh", "-c", node->string, NULL}; // Execute command
            execvp(args[0], args);
            perror("execvp"); // If execvp fails
            exit(EXIT_FAILURE);
        }
        else if (pid > 0) // Parent process
        {
            waitpid(pid, NULL, 0); // Wait for the child to finish
        }
        else
        {
            perror("fork");
        }
    }

    // Handle pipes (`|`)
    else if (node->token == 4) // Assuming 4 is PIPE (`|`)
    {
        int pipefd[2];
        if (pipe(pipefd) == -1)
        {
            perror("pipe");
            return;
        }

        pid_t pid = fork();
        if (pid == 0) // First child (left command)
        {
            close(pipefd[0]); // Close read end
            dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
            close(pipefd[1]);

            execute_ast(node->left); // Execute left command
            exit(EXIT_SUCCESS);
        }
        else if (pid > 0)
        {
            pid_t pid2 = fork();
            if (pid2 == 0) // Second child (right command)
            {
                close(pipefd[1]); // Close write end
                dup2(pipefd[0], STDIN_FILENO); // Redirect stdin from pipe
                close(pipefd[0]);

                execute_ast(node->right); // Execute right command
                exit(EXIT_SUCCESS);
            }
            else if (pid2 > 0)
            {
                close(pipefd[0]);
                close(pipefd[1]);
                waitpid(pid, NULL, 0);
                waitpid(pid2, NULL, 0);
            }
            else
            {
                perror("fork");
            }
        }
        else
        {
            perror("fork");
        }
    }

    // Handle Redirections (`>`, `<`, `>>`)
    else if (node->token == 6) // Assuming 6 is `>` redirection
    {
        int fd = open(node->right->string, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("open");
            return;
        }

        pid_t pid = fork();
        if (pid == 0)
        {
            dup2(fd, STDOUT_FILENO); // Redirect stdout to file
            close(fd);
            execute_ast(node->left); // Execute left command
            exit(EXIT_SUCCESS);
        }
        else if (pid > 0)
        {
            close(fd);
            waitpid(pid, NULL, 0);
        }
        else
        {
            perror("fork");
        }
    }
}


