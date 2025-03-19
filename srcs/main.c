#include "../include/main.h"

// Define AST Node Types
typedef enum e_node_type
{
    NODE_COMMAND,
    NODE_PIPE,
    NODE_AND,
    NODE_OR
} t_node_type;

// AST Node Structure
typedef struct s_ast
{
    t_node_type type;
    char **args;         // Command arguments (for NODE_COMMAND)
    struct s_ast *left;  // Left child (used for PIPE, AND, OR)
    struct s_ast *right; // Right child (used for PIPE, AND, OR)
} t_ast; 

// Function to Create an AST Node
t_ast *create_ast_node(t_node_type type, char **args, t_ast *left, t_ast *right)
{
    t_ast *node = malloc(sizeof(t_ast));
    if (!node)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    node->args = args;
    node->left = left;
    node->right = right;
    return node;
}

// Recurrent Function! 
void execute_ast(t_ast *node)
{
    if (!node)
        return;

    if (node->type == NODE_COMMAND)
    {
        pid_t pid = fork();
        if (pid == 0) // Child Process
        {
            if (execvp(node->args[0], node->args) == -1)
            {
                perror("minishell");
                exit(EXIT_FAILURE);
            }
        }
        else if (pid > 0) // Parent Process
            wait(NULL);
        else
            perror("fork");
    }
    else if (node->type == NODE_PIPE)
    {
        int fd[2];
        if (pipe(fd) == -1)
        {
            perror("pipe");
            return;
        }
        pid_t pid1 = fork();
        if (pid1 == 0) // Left Command (First)
        {
            close(fd[0]);         // Close unused read end
            dup2(fd[1], STDOUT_FILENO); // Redirect stdout to pipe
            close(fd[1]);         // Close write end
            execute_ast(node->left);
            exit(0);
        }

        pid_t pid2 = fork();
        if (pid2 == 0) // Right Command (Second)
        {
            close(fd[1]);          // Close unused write end
            dup2(fd[0], STDIN_FILENO); // Redirect stdin from pipe
            close(fd[0]);          // Close read end
            execute_ast(node->right);
            exit(0);
        }

        close(fd[0]);
        close(fd[1]);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
    }
    else if (node->type == NODE_AND)
    {
        execute_ast(node->left);
        execute_ast(node->right);
    }
    else if (node->type == NODE_OR)
    {
        execute_ast(node->left);
        execute_ast(node->right);
    }
}

// Dummy Function to Parse Input into an AST (Replace with real parser)
t_ast *parse_input(char *input)
{
    char **args = malloc(2 * sizeof(char *));
    args[0] = strdup(input);
    args[1] = NULL;
    return create_ast_node(NODE_COMMAND, args, NULL, NULL);
}

int main(void)
{
    char *input;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
        {
            printf("exit\n");
            break;
        }
        if (*input)
        {
            add_history(input);
            t_ast *ast = parse_input(input); // Convert input to AST
            execute_ast(ast);                // Execute AST
        }
        free(input);
    }
    return 0;
}
