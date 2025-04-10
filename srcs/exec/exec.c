#include "exec.h"

// static void execute_builtin(t_token *node)
// {
//     char    **cmd;
//     char    *f;
//     cmd = ft_split(node->string, 32);
//     if(!cmd)
//         return;
//     f = cmd[0];
//     (void)f;
// }

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
}

static void execute_with_redirection(t_token *node, int flags, char **envp)
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

        execute_ast(node->left, envp);
        exit(EXIT_SUCCESS);
    }
    waitpid(pid, NULL, 0);
}

// 입력 리다이렉션 처리 (<)
void redirect_input_and_execute(t_token *node, char **envp)
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
        execute_ast(node->left, envp); // 입력 리다이렉션 후 왼쪽 명령 실행
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


static void  execute_pipe(t_token *node, char **envp)
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

        execute_ast(node->left, envp);
        exit(EXIT_SUCCESS);
    }

    pid_t right_pid = fork();
    if (right_pid == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        execute_ast(node->right, envp);
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


void ft_execute_builtin(t_token *node, char **envp)
{
    if(ft_strncmp(node->string, "echo", ft_strlen("echo")) == 0)
        ft_echo(node->string, 0);
    if(ft_strncmp(node->string, "pwd", ft_strlen("pwd")) == 0)
        ft_pwd(node);
    if(ft_strncmp(node->string, "cd", ft_strlen("cd")) == 0)
    {
        ft_cd(node->string);
    }
    if(ft_strncmp(node->string, "export", ft_strlen("export")) == 0)
        ft_export(&envp, node->string);
} 


void execute_ast(t_token *node, char **envp)
{
    if (!node)
        return;

    switch (node->token)
    {
        case 1: // CMD
            //printf("start case 1 :%s\n", node->string);
            execute_command(node->string);
            break;
            
        case 4: // PIPE
            //printf("start case 4:%s\n", node->string);
            execute_pipe(node, envp);
            break;

		case 5: // INPUT REDIRECTION (<)
            //printf("start case 5::%s\n", node->string);
			redirect_input_and_execute(node, envp);
			break;

        case 6: // >
            //printf("start case 6::%s\n", node->string);
            execute_with_redirection(node, O_WRONLY | O_CREAT | O_TRUNC, envp);
            break;

        case 7: // >>
            //printf("start case 7::%s\n", node->string);
            execute_with_redirection(node, O_WRONLY | O_CREAT | O_APPEND, envp);
            break;

		case 10: // HEREDOC (<<) //added new codes for fixing unexpected crash after heredoc
        {
            //printf("start case 10::%s\n", node->string);
            int original_stdin = dup(STDIN_FILENO); // Save the original stdin
            if (original_stdin == -1)
            {
                perror("dup failed");
                return;
            }
            heredoc_redirect(node);
            execute_ast(node->left, envp); // Execute the command with redirected input
            if (dup2(original_stdin, STDIN_FILENO) == -1) // Restore original stdin
            {
                perror("dup2 failed to restore stdin");
            }
            close(original_stdin);
            break;
        }
        case 12: // builtin part
        {
            ft_execute_builtin(node, envp);
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

