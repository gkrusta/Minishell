#include "minishell.h"

/*
void	exec_comm(t_cmd *node, t_shell *shell)
{
	int	i;

	i = 8;
	while (i > 0)
	{
		node->args[i] = node->args[i - 1];
		i--;
	}
	node->args[0] = node->cmd;
	i = 0;
	while (node->args[i])
	{
		printf("  arg %i: %s\n", i, node->args[i]);
		i++;
	}
	execve(node->cmd_path, node->args, shell->env);
}

void	fork_child(t_cmd *node, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close((node->outfile - 1));
		dup2(node->outfile, STDOUT_FILENO);
		exec_comm(node, shell);
	}
	waitpid(pid, NULL, 0);
	dup2((node->outfile - 1), STDIN_FILENO);
	close((node->outfile - 1));
}

void	execute_nodes(t_cmd **nodes, t_shell *shell)
{
	t_cmd	*node;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		node = *nodes;
		if (node)
			dup2(node->infile, STDIN_FILENO);
		while (node->next)
		{
			fork_child(node, shell);
			node = node->next;
		}
		close(node->infile);
		dup2(node->outfile, STDOUT_FILENO);
		exec_comm(node, shell);
	}
	waitpid(pid, NULL, 0);
	printf("despues de waitpid\n");
}
*/



void execute_nodes(t_cmd **nodes, t_shell *shell) {
    t_cmd *current_node = *nodes;
    int prev_pipe[2] = {STDIN_FILENO, -1};  // Inicializamos el pipe de entrada con STDIN

    while (current_node != NULL) {
        int next_pipe[2] = {-1, -1};  // Inicializamos el pipe de salida a -1

        if (current_node->next != NULL) {
            // Si hay un nodo siguiente, crea un nuevo pipe
            if (pipe(next_pipe) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {  // Proceso hijo
            // Configurar redirección de entrada
            if (current_node->infile != STDIN_FILENO) {
                dup2(current_node->infile, STDIN_FILENO);
                close(current_node->infile);
            } else if (prev_pipe[0] != STDIN_FILENO) {
                dup2(prev_pipe[0], STDIN_FILENO);
            }

            // Configurar redirección de salida
            if (current_node->next != NULL) {
                dup2(next_pipe[1], STDOUT_FILENO);
                close(next_pipe[0]);
            } else if (current_node->outfile != STDOUT_FILENO) {
                dup2(current_node->outfile, STDOUT_FILENO);
                close(current_node->outfile);
            }

            // Ejecutar el comando
            execve(current_node->cmd_path, current_node->args, shell->env);
            perror("execve");  // Solo se ejecuta si execve falla
            exit(EXIT_FAILURE);
        } else {  // Proceso padre
            if (prev_pipe[0] != STDIN_FILENO) {
                close(prev_pipe[0]);
            }

            if (prev_pipe[1] != -1) {
                close(prev_pipe[1]);
            }

            if (current_node->outfile != STDOUT_FILENO) {
                close(current_node->outfile);
            }

            // Esperar a que el proceso hijo termine
            waitpid(pid, NULL, 0);
        }

        current_node = current_node->next;
        prev_pipe[0] = next_pipe[0];
        prev_pipe[1] = next_pipe[1];
    }
}
