#include "exec.h"

static void execute_pipe_recursive(t_token *node, char ***envp);
void ft_execute_builtin(t_token *node, char ***envp);
static void execute_pipe_recursive(t_token *node, char ***envp);

void close_all_heredoc_fds_in_tree(t_token *node) {
    if (!node) {
        return;
    }
    // Close FD if present and VALID (>= 0) for this node
    if (node->heredoc_pipe_fd >= 0) { // Check if FD is valid
        if (close(node->heredoc_pipe_fd) == -1) {
            perror("close (heredoc fd in tree)");
            // Continue anyway, try to close others
        }
        // Mark FD as invalid after closing. Optionally reset state.
        node->heredoc_pipe_fd = -1;
        // node->heredoc_state = HD_NOT_PROCESSED; // Optional: Reset state? Or keep as OK/FAILED? Better keep.
    }
    // Recurse through children
    close_all_heredoc_fds_in_tree(node->left);
    close_all_heredoc_fds_in_tree(node->right);
}

int preprocess_heredocs(t_token *node) 
{
    if (!node) {
        return 0; // Success for null node
    }

    // --- Check State for THIS node FIRST ---
    // If it's a HEREDOC node that has already been processed or failed,
    // skip processing it again, but MUST still process children.
    if (node->token == HEREDOC && node->heredoc_state != HD_NOT_PROCESSED) {
        // Still need to traverse children for *other* potential heredocs below this one.
        if (preprocess_heredocs(node->left) == -1) return -1;
        if (preprocess_heredocs(node->right) == -1) return -1;
        // Return the stored status of this node.
        return (node->heredoc_state == HD_PROCESSING_FAILED) ? -1 : 0;
    }

    // --- Process THIS node (if it's an unprocessed HEREDOC) ---
    if (node->token == HEREDOC /* && node->heredoc_state == HD_NOT_PROCESSED implied */) 
	{
        if (!node->right || !node->right->string) 
		{
            fprintf(stderr, "minishell: syntax error near heredoc (missing delimiter)\n");
            node->heredoc_state = HD_PROCESSING_FAILED; // Mark as failed
            node->heredoc_pipe_fd = -1;
            return -1; // Failure
        }

		// Inside preprocess_heredocs, after the call:
		node->heredoc_pipe_fd = read_heredoc_to_pipe(node->right->string);
		fprintf(stderr, "[DEBUG preprocess] Heredoc for '%s': read_heredoc_to_pipe returned FD=%d\n",
				node->right->string, node->heredoc_pipe_fd); // DEBUG Print

		if (node->heredoc_pipe_fd == -1) {
			fprintf(stderr, "[DEBUG preprocess] Setting state to HD_PROCESSING_FAILED for '%s'\n", node->right->string); // DEBUG Print
			node->heredoc_state = HD_PROCESSING_FAILED;
			return -1;
		}
		// Success!
		fprintf(stderr, "[DEBUG preprocess] Setting state to HD_PROCESSED_OK for '%s'\n", node->right->string); // DEBUG Print
		node->heredoc_state = HD_PROCESSED_OK;
    }

    // --- Recursively process children AFTER potentially processing this node ---
    // This ensures nested heredocs are found and processed.
    if (preprocess_heredocs(node->left) == -1) {
        // Propagate failure. If this node just opened an FD, it will be
        // cleaned up later by close_all_heredoc_fds_in_tree if execution fails.
        return -1;
    }
    if (preprocess_heredocs(node->right) == -1) {
        // Propagate failure.
        return -1;
    }

    // Return success (0) if this node wasn't a HEREDOC, or if it was a HEREDOC
    // and was successfully processed just now (state is HD_PROCESSED_OK).
    // If it was a HEREDOC and failed just now, -1 was already returned.
    // If it was a HEREDOC processed previously, the check at the top handles it.
    if (node->token == HEREDOC) {
         return (node->heredoc_state == HD_PROCESSING_FAILED) ? -1 : 0;
    } else {
         return 0; // Success for non-heredoc node if children succeeded.
    }
}

static void execute_command(const char *command)
{
	char *args[] = {"/bin/sh", "-c", (char *)command, NULL};
	execvp(args[0], args);
	perror("execvp");
	exit(127);
}

// Returns 0 on success, -1 on failure
static int apply_single_redirection(t_token *redir_node) {
     int fd = -1;
     int target_fd = -1; // STDIN_FILENO or STDOUT_FILENO
     int flags = 0;
     mode_t mode = 0644; // Default mode S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

     // Check for target filename/delimiter node
     if (!redir_node->right || !redir_node->right->string) {
         fprintf(stderr, "minishell: syntax error near redirection\n");
         // TODO: Set exit status 258?
         return -1; // Signal failure
     }
     const char* target = redir_node->right->string;

     switch (redir_node->token) {
         case REDIR_WRITE: // >
             flags = O_WRONLY | O_CREAT | O_TRUNC;
             target_fd = STDOUT_FILENO;
             fd = open(target, flags, mode);
             break;
         case REDIR_WRITE_A: // >>
             flags = O_WRONLY | O_CREAT | O_APPEND;
             target_fd = STDOUT_FILENO;
             fd = open(target, flags, mode);
             break;
         case REDIR_OPEN: // <
             flags = O_RDONLY;
             target_fd = STDIN_FILENO;
             fd = open(target, flags);
             break;
         case HEREDOC: // <<
             // Check state and FD from preprocessing
             if (redir_node->heredoc_state != HD_PROCESSED_OK || redir_node->heredoc_pipe_fd < 0) {
                 fprintf(stderr, "minishell: internal error - heredoc not ready for apply_single_redirection\n");
                 return -1; // Signal failure
             }
             fd = redir_node->heredoc_pipe_fd; // Use the pre-filled FD
             target_fd = STDIN_FILENO;
             // DO NOT open() here, we use the existing FD
             break;
         default:
             fprintf(stderr, "minishell: internal error - unexpected token (%d) in apply_single_redirection\n", redir_node->token);
             return -1; // Signal failure
     }

     // Check open() result (for non-heredoc cases)
     if (redir_node->token != HEREDOC && fd == -1) {
         perror(target); // Print specific file error
         // TODO: Set exit status 1?
         return -1; // Signal failure
     }

     // Perform the redirection
     if (dup2(fd, target_fd) == -1) {
         perror("dup2 in apply_single_redirection");
         // Close the fd we opened/retrieved if it wasn't the target_fd itself
         // and ONLY IF it wasn't the heredoc FD (which gets closed later elsewhere)
         if (fd != target_fd && redir_node->token != HEREDOC) {
             close(fd);
         }
         // TODO: Set exit status 1?
         return -1; // Signal failure
     }

     // Close the original file descriptor `fd` IF it wasn't the heredoc FD
     // AND if it wasn't the same as the target FD (e.g. redirecting fd 1 to 1).
     // The heredoc FD must persist in the child until it's no longer needed (before exec or exit),
     // and it must be closed by the PARENT process eventually.
     if (redir_node->token != HEREDOC && fd != target_fd) {
         if (close(fd) == -1) {
             perror("close in apply_single_redirection");
             // Continue, but maybe log this?
         }
     }

     return 0; // Success
}

// --- New recursive execution function (runs in child processes) ---
static void execute_node_recursive(t_token *node, char ***envp) {
    if (!node) exit(EXIT_SUCCESS); // Valid end of a branch?

    switch (node->token) {
        case REDIR_WRITE: // >
        case REDIR_WRITE_A: // >>
        case REDIR_OPEN:  // <
        case HEREDOC:         // <<
            // 1. Apply this specific redirection
            if (apply_single_redirection(node) == -1) {
                 // Error already printed by apply_single_redirection
                 exit(EXIT_FAILURE); // Exit this child process on redirection failure
            }
            // 2. Execute the command part (left child)
            execute_node_recursive(node->left, envp);
            // The line below should not be reached if execute_node_recursive exits/execs
            exit(EXIT_FAILURE); // Exit if recursive call unexpectedly returns

        case PIPE:
            execute_pipe_recursive(node, envp);
            // exit() is called inside execute_pipe_recursive
            break; // Should not be reached

        case CMD:
            // Ready to execute the final command in this branch
            execute_command(node->string); // Uses execvp, will exit(127) on failure
            break; // Should not be reached

        case BUILTIN:
             // Execute non-state-modifying builtin
             // TODO: Handle builtin exit status properly
             ft_execute_builtin(node, envp);
             exit(EXIT_SUCCESS); // Assuming success for now
             break;

        case WORD: // Should not be directly executed (e.g., filename/delimiter)
             fprintf(stderr,"minishell: Error: Trying to execute a STRING node (%s)\n", node->string);
             exit(EXIT_FAILURE);

        default:
            fprintf(stderr, "minishell: Unexpected node type for execution: %d\n", node->token);
            exit(EXIT_FAILURE);
    }
    // Fallback exit, should ideally not be reached
    exit(EXIT_FAILURE);
}


int read_heredoc_to_pipe(const char *delimiter) {
    int pipefd[2];
    if (pipe(pipefd) == -1) { // Possibility 1: pipe() failed
        perror("pipe (heredoc)");
        return -1;
    }

    char *line = NULL;
    bool read_success = true; // Assuming you added this flag

        fprintf(stderr, "[DEBUG read_heredoc] Expecting delimiter: \"%s\"\n", delimiter); // DEBUG

    while (1)
    {
        line = readline("> ");
        if (!line) {
            fprintf(stderr, "minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
            read_success = false;
            break;
        }

        // --- DETAILED DEBUG PRINT ---
        fprintf(stderr, "[DEBUG read_heredoc] Read line content: \"");
        for (int i = 0; line[i]; i++) { // Print char by char
            if (line[i] == '\n') fprintf(stderr, "\\n"); // Show newline explicitly
            else if (line[i] == '\r') fprintf(stderr, "\\r"); // Show carriage return explicitly
            else if (isprint(line[i])) fprintf(stderr, "%c", line[i]); // Print printable chars
            else fprintf(stderr, "\\x%02x", (unsigned char)line[i]); // Print hex for others
        }
        fprintf(stderr, "\" (Length: %zu)\n", strlen(line));
        // --- END DEBUG PRINT ---

        // The comparison:
        if (strcmp(line, delimiter) == 0) {
            fprintf(stderr, "[DEBUG read_heredoc] strcmp SUCCESS!\n"); // DEBUG
            free(line);
            break;
        } else {
             fprintf(stderr, "[DEBUG read_heredoc] strcmp FAILED.\n"); // DEBUG
        }

        // ... write to pipe ...
         ssize_t line_len = strlen(line);
         if (write(pipefd[1], line, line_len) != line_len || write(pipefd[1], "\n", 1) != 1) {
             perror("write (heredoc pipe)");
             free(line);
             read_success = false;
             close(pipefd[0]);
             close(pipefd[1]);
             return -1;
         }
        free(line);
    }
    // ... close FDs and return ...
    close(pipefd[1]);
    if (read_success) {
        return pipefd[0];
    } else {
        close(pipefd[0]);
        return -1;
    }
}

/*
static void execute_pipe(t_token *node, char ***envp) {
    if (!node || node->token != PIPE || !node->left || !node->right) {
        fprintf(stderr, "minishell: Invalid pipe structure\n"); return;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe (main)"); return;
    }

    pid_t left_pid = fork();
    if (left_pid == -1) {
        perror("fork (pipe left)"); close(pipefd[0]); close(pipefd[1]); return;
    }

    if (left_pid == 0) { // Left Child
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2 stdout to pipe"); close(pipefd[1]); exit(EXIT_FAILURE);
        }
        close(pipefd[1]);
        execute_ast(node->left, envp); // Execute left side
        exit(EXIT_SUCCESS); // Exit after execution
    }

    pid_t right_pid = fork();
    if (right_pid == -1) {
        perror("fork (pipe right)"); close(pipefd[0]); close(pipefd[1]);
        waitpid(left_pid, NULL, 0); return;
    }

    if (right_pid == 0) { // Right Child
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2 stdin from pipe"); close(pipefd[0]); exit(EXIT_FAILURE);
        }
        close(pipefd[0]);
        execute_ast(node->right, envp); // Execute right side
        exit(EXIT_SUCCESS); // Exit after execution
    }

    // Parent of pipe
    close(pipefd[0]);
    close(pipefd[1]);
    int left_status, right_status;
    waitpid(left_pid, &left_status, 0);
    waitpid(right_pid, &right_status, 0);
    // TODO: Set global exit status based on right_status
}
*/

// --- Modified pipe execution using the recursive approach ---
// This function now runs within a child process context.
// It creates grandchildren and exits based on the rightmost grandchild's status.
static void execute_pipe_recursive(t_token *node, char ***envp) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE); // Exit the current child process
    }

    pid_t left_pid = fork();
    if (left_pid == -1) {
        perror("fork (pipe left)");
        close(pipefd[0]); close(pipefd[1]);
        exit(EXIT_FAILURE);
    }

    if (left_pid == 0) { // Grandchild 1 (Left Side)
        close(pipefd[0]); // Close unused read end
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2 stdout pipe");
            close(pipefd[1]); // Close write end before exiting
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]); // Close original write end
        // Execute left side recursively
        execute_node_recursive(node->left, envp);
        exit(EXIT_FAILURE); // Should have been replaced by exec or exited specifically
    }

    // Only the original child continues here... forks the right side
    pid_t right_pid = fork();
    if (right_pid == -1) {
        perror("fork (pipe right)");
        close(pipefd[0]); close(pipefd[1]); // Close pipe in current process
        // Kill the left child? More complex signal handling needed for robustness.
        waitpid(left_pid, NULL, 0); // Wait for left child before exiting
        exit(EXIT_FAILURE);
    }

    if (right_pid == 0) { // Grandchild 2 (Right Side)
        close(pipefd[1]); // Close unused write end
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2 stdin pipe");
            close(pipefd[0]); // Close read end before exiting
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]); // Close original read end
        // Execute right side recursively
        execute_node_recursive(node->right, envp);
        exit(EXIT_FAILURE); // Should have been replaced by exec or exited specifically
    }

    // Parent of pipe (original child process from execute_ast) closes its pipe FDs
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both grandchildren
    int left_status, right_status;
    waitpid(left_pid, &left_status, 0);
    waitpid(right_pid, &right_status, 0);

    // Exit this original child process with the status of the rightmost command
    int exit_status = EXIT_FAILURE; // Default to failure
    if (WIFEXITED(right_status)) {
        exit_status = WEXITSTATUS(right_status);
    } else if (WIFSIGNALED(right_status)) {
        // Handle signal termination if necessary (e.g., exit code 128 + signal number)
        // exit_status = 128 + WTERMSIG(right_status);
    }
    exit(exit_status); // Exit the intermediate child process
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

bool is_state_modifying_builtin(const char *cmd_name) {
    if (!cmd_name) return false;
    // TODO: Improve this check if cmd_name can contain args (e.g., parse first word)
    return strcmp(cmd_name, "cd") == 0 ||
           strcmp(cmd_name, "export") == 0 ||
           strcmp(cmd_name, "unset") == 0 ||
           strcmp(cmd_name, "exit") == 0;
}

// Main execution function (called after parsing)
void execute_ast(t_token *node, char ***envp) {
    if (!node) return;

    // --- Phase 1: Preprocess ALL Heredocs ---
    if (preprocess_heredocs(node) == -1) {
        fprintf(stderr, "minishell: heredoc processing failed\n");
        close_all_heredoc_fds_in_tree(node); // Close any FDs potentially opened
        // TODO: Set global exit status (e.g., 1 or 2)
        return;
    }

    // --- Phase 2: Execute ---
    // TODO: Add proper handling for builtins like cd, export, unset, exit
    // that MUST run in the main shell process. This requires checking
    // if 'node' represents ONLY such a builtin possibly with redirections.
    // This is complex as it involves saving/restoring stdio in the parent.
    /* Example Check (simplified):
    if (node->token == BUILTIN && is_state_modifying_builtin(node->string)) {
        // ... check for pipes/complex structures ...
        // If simple: apply redirections locally, run builtin, restore stdio
        // For now, we skip this and fork for builtins too (except exit maybe)
        if (strcmp(node->string, "exit") == 0) {
             // Handle exit directly? Needs careful thought about args/cleanup.
             // ft_exit(0); // Might exit too early without cleanup?
        }
    }
    */

    // Fork to execute the command tree
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork (execute_ast)");
        close_all_heredoc_fds_in_tree(node); // Close heredocs in parent on fork failure
        // TODO: Set exit status
        return;
    }

    if (pid == 0) { // Child Process
        // Child executes the command tree recursively, handling I/O setup internally
        execute_node_recursive(node, envp);
        // If execute_node_recursive returns unexpectedly (it shouldn't)
        exit(EXIT_FAILURE);
    } else { // Parent Process
        // Parent MUST close its copies of the heredoc read FDs
        close_all_heredoc_fds_in_tree(node);

        // Wait for the main child process
        int status;
        waitpid(pid, &status, 0);

        // TODO: Set global exit status based on the child's status
        // e.g., g_exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : 128 + WTERMSIG(status);
    }
}