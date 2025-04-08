#include "exec.h"

static void execute_command(const char *command)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    if (pid == 0)
    {
        char *args[] = {"/bin/sh", "-c", (char *)command, NULL};
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    waitpid(pid, NULL, 0);
	printf("\n");
}

static void execute_with_redirection(t_token *node, int flags)
{
    if (!node->left || !node->right)
    {
        fprintf(stderr, "Invalid AST structure for redirection.\n");
        return;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        int fd = open(node->right->string, flags, 0644);
        if (fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);

        execute_ast(node->left);
        exit(EXIT_SUCCESS);
    }
    waitpid(pid, NULL, 0);
}

// 입력 리다이렉션 처리 (<)
void redirect_input_and_execute(t_token *node)
{
    if (!node->left || !node->right)
    {
        fprintf(stderr, "Input redirection error: Missing left/right node.\n");
        return;
    }

    int fd = open(node->right->string, O_RDONLY);
    if (fd == -1)
    {
        perror("open (input redirection)");
        return;
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("dup2 (input redirection)");
            close(fd);
            exit(EXIT_FAILURE);
        }
        close(fd);
        execute_ast(node->left); // 입력 리다이렉션 후 왼쪽 명령 실행
        exit(EXIT_SUCCESS);
    }
    else if (pid > 0)
    {
        close(fd);
        waitpid(pid, NULL, 0);
    }
    else
        perror("fork (input redirection)");
}


static void execute_pipe(t_token *node)
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }

    pid_t left_pid = fork();
    if (left_pid == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execute_ast(node->left);
        exit(EXIT_SUCCESS);
    }

    pid_t right_pid = fork();
    if (right_pid == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        execute_ast(node->right);
        exit(EXIT_SUCCESS);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(left_pid, NULL, 0);
    waitpid(right_pid, NULL, 0);
}

void heredoc_redirect(t_token *node)
{
    if (!node || !node->right)
    {
        fprintf(stderr, "Heredoc error: Missing delimiter or command.\n");
        return;
    }

    char *delimiter = node->right->string;
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    else if (pid == 0) // Child process for heredoc reading
    {
        close(pipefd[0]); // Close the read end, we're only writing

        char *line;
        while (1)
        {
            //line = readline("> ");
			line = readline("heredoc> ");
            if (!line || strcmp(line, delimiter) == 0) // Stop when delimiter is found
            {
                free(line);
                break;
            }
            write(pipefd[1], line, strlen(line));
            write(pipefd[1], "\n", 1); // Add newline to each line
            free(line);
        }

        close(pipefd[1]); // Close the write end
        exit(0); // End the child process
    }
    else // Parent process
    {
        close(pipefd[1]); // Close write end, we're only reading
        waitpid(pid, NULL, 0);

        // Redirect stdin to read from the pipe
        if (dup2(pipefd[0], STDIN_FILENO) == -1)
        {
            perror("dup2 failed");
            close(pipefd[0]);
            return;
        }
        close(pipefd[0]);
    }
}


void execute_ast(t_token *node)
{
    if (!node)
        return;

    switch (node->token)
    {
        case 1: // CMD
            execute_command(node->string);
            break;

        case 4: // PIPE
            execute_pipe(node);
            break;

		case 5: // INPUT REDIRECTION (<)
			redirect_input_and_execute(node);
			break;

        case 6: // >
            execute_with_redirection(node, O_WRONLY | O_CREAT | O_TRUNC);
            break;

        case 7: // >>
            execute_with_redirection(node, O_WRONLY | O_CREAT | O_APPEND);
            break;

		case 10: // HEREDOC (<<) //added new codes for fixing unexpected crash after heredoc
        {
            int original_stdin = dup(STDIN_FILENO); // Save the original stdin
            if (original_stdin == -1)
            {
                perror("dup failed");
                return;
            }
            heredoc_redirect(node);
            execute_ast(node->left); // Execute the command with redirected input
            if (dup2(original_stdin, STDIN_FILENO) == -1) // Restore original stdin
            {
                perror("dup2 failed to restore stdin");
            }
            close(original_stdin);
            break;
        }
		/*
		case 10: // HEREDOC (<<)
            heredoc_redirect(node);
            execute_ast(node->left); // Execute the command after setting up heredoc. why? 
            break;
		*/
        default:
            fprintf(stderr, "Unknown token type: %d\n", node->token);
            break;
    }
}

