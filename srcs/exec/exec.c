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
/*
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

        execute_ast(node->left, envp);
        exit(EXIT_SUCCESS);
    }
    waitpid(pid, NULL, 0);
}
*/
// 입력 리다이렉션 처리 (<)
void redirect_input_and_execute(t_token *node, char ***envp)
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
        execute_ast(node->left, &envp); // 입력 리다이렉션 후 왼쪽 명령 실행
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

static void execute_pipe(t_token *node, char ***envp)
{
    // 추가된 부분: 왼쪽 자식이 출력 리다이렉션인지 확인
    if (node->left && (node->left->token == 6 /* > */ || node->left->token == 7 /* >> */))
    {
        // 1. 왼쪽 리다이렉션 실행 (이 안에서 fork/exec/wait 발생)
        execute_ast(node->left, envp);

        // 2. 오른쪽 명령어 실행 (stdin은 닫힌 상태로)
        pid_t right_pid = fork();
        if (right_pid == -1)
        {
            perror("fork (pipe right side after redirect)");
            return;
        }

        if (right_pid == 0) // 오른쪽 자식 프로세스
        {
            // stdin을 닫거나 /dev/null로 연결하여 입력 없음을 명시
            int dev_null_fd = open("/dev/null", O_RDONLY);
            if (dev_null_fd != -1) {
                 if (dup2(dev_null_fd, STDIN_FILENO) == -1) {
                     perror("dup2 stdin to /dev/null");
                 }
                 close(dev_null_fd);
            } else {
                 close(STDIN_FILENO); // /dev/null 열기 실패 시 그냥 stdin 닫기
            }

            // 오른쪽 노드 실행
            execute_ast(node->right, envp);
            exit(EXIT_SUCCESS); // 자식 프로세스 종료
        }

        // 부모 프로세스: 오른쪽 자식 기다리기
        waitpid(right_pid, NULL, 0);
        return; // 특별 처리 완료, 기존 파이프 로직 건너뛰기
    }

    // --- 기존 파이프 로직 (왼쪽이 리다이렉션이 아닐 경우) ---
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }

    pid_t left_pid = fork();
    if (left_pid == -1) {
        perror("fork (pipe left)");
        close(pipefd[0]);
        close(pipefd[1]);
        return;
    }

    if (left_pid == 0) // 왼쪽 자식 (파이프에 쓰기)
    {
        close(pipefd[0]); // 읽기용 fd 닫기
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) { // stdout을 파이프 쓰기용 fd로 복제
             perror("dup2 stdout to pipe");
             close(pipefd[1]);
             exit(EXIT_FAILURE);
        }
        close(pipefd[1]); // 복제 후 원본 fd 닫기
        execute_ast(node->left, envp); // 왼쪽 노드 실행
        exit(EXIT_SUCCESS);
    }

    pid_t right_pid = fork();
     if (right_pid == -1) {
        perror("fork (pipe right)");
        close(pipefd[0]);
        close(pipefd[1]);
        // left_pid 처리? (이미 실행 중일 수 있음)
        waitpid(left_pid, NULL, 0); // 일단 왼쪽 자식 기다려보기
        return;
    }

    if (right_pid == 0) // 오른쪽 자식 (파이프에서 읽기)
    {
        close(pipefd[1]); // 쓰기용 fd 닫기
         if (dup2(pipefd[0], STDIN_FILENO) == -1) { // stdin을 파이프 읽기용 fd로 복제
             perror("dup2 stdin from pipe");
             close(pipefd[0]);
             exit(EXIT_FAILURE);
         }
        close(pipefd[0]); // 복제 후 원본 fd 닫기
        execute_ast(node->right, &envp); // 오른쪽 노드 실행
        exit(EXIT_SUCCESS);
    }

    // 부모 프로세스: 파이프 fd 닫고 자식들 기다리기
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(left_pid, NULL, 0);
    waitpid(right_pid, NULL, 0);
}

/* work well but hope next version is better
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

        // Check if the left side of the *parent* was an output redirection
        if (node->parent && (node->parent->token == 6 || node->parent->token == 7) && node == node->parent->right)
        {
            // Redirect input from the file specified in the grandparent
            if (node->parent->right) // This should be the filename node
            {
                int fd = open(node->parent->right->string, O_RDONLY);
                if (fd != -1)
                {
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                    close(pipefd[0]); // Close the read end of the pipe as we are reading from a file
                }
                else
                {
                    perror("open (reading from redirected file)");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else
        {
            dup2(pipefd[0], STDIN_FILENO);
        }
        close(pipefd[0]);

        execute_ast(node->right);
        exit(EXIT_SUCCESS);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(left_pid, NULL, 0);
    waitpid(right_pid, NULL, 0);
}
*/

/*
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
*/

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

void ft_execute_builtin(t_token *node, char ***envp)
{
    if(ft_strncmp(node->string, "echo", ft_strlen("echo")) == 0)
        ft_echo(node->string, 0);
    if(ft_strncmp(node->string, "pwd", ft_strlen("pwd")) == 0)
        ft_pwd(node);
    if(ft_strncmp(node->string, "cd", ft_strlen("cd")) == 0)
        ft_cd(node->string);
    if(ft_strncmp(node->string, "export", ft_strlen("export")) == 0)
        ft_export(envp, node->string);
    if(ft_strncmp(node->string, "exit", ft_strlen("exit")) == 0)
        ft_exit(0);
    if(ft_strncmp(node->string, "unset", ft_strlen("unset")) == 0)
        ft_unset(node->string,envp);
} 

void execute_ast(t_token *node, char ***envp) 
{
    if (!node) {
        return;
    }

    t_redir *redir_list = NULL;
    t_token *command_node = node;


    while (command_node &&((command_node->token >= 5 && command_node->token <= 7)))//not heredoc here
    {
        if (!command_node->right || !command_node->right->string) {
            fprintf(stderr, "minishell: syntax error near redirection\n");
            free_redir_list(redir_list); 
            return;
        }
        add_redirection_to_list(&redir_list, command_node->token, command_node->right->string);
        command_node = command_node->left;
    }

    if (redir_list != NULL) 
	{
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork failed");
            free_redir_list(redir_list);
            return;
        }

        if (pid == 0) 
		{
            if (apply_redirections(redir_list) == -1) 
			{
                free_redir_list(redir_list); // Free list in child before exiting
                exit(EXIT_FAILURE); // Child exits on redirection error
            }
             execute_ast(command_node, &envp);
             exit(EXIT_SUCCESS);

        } 
		else 
		{ // Parent process
            free_redir_list(redir_list); // Free the list in the parent
            waitpid(pid, NULL, 0);
        }

    } 
	else 
	{
        switch (command_node->token) // Use command_node here, as it's the relevant node
        {
			case 1: // CMD
				execute_command(node->string);
				break;

			case 4: // PIPE
				execute_pipe(node, envp);
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
				execute_ast(node->left, &envp); // Execute the command with redirected input
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
			default:
				fprintf(stderr, "minishell: Unknown or unhandled token type: %d\n", command_node->token);
				break;
        }
    }
     // Don't forget to free the redir_list if allocated, although it should be freed
     // within the branches above. Adding a failsafe might be good if error paths are complex.
     //free_redir_list(redir_list); // Probably redundant here.
}

/* april 9 before take care of multiple redirecton 
void execute_ast(t_token *node)
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
        default:
            fprintf(stderr, "Unknown token type: %d\n", node->token);
            break;
    }
}
*/

