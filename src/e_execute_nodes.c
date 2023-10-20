#include "minishell.h"

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
	execve(node->cmd_path, node->args, shell->env);
}

void	fork_child(t_cmd *node, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(node->infile);
		dup2(node->outfile, STDOUT_FILENO);
		printf("proceso HIJO outfile: %i\n", node->outfile);
		exec_comm(node, shell);
	}
	close(node->outfile);
	dup2(node->infile, STDIN_FILENO);
	printf("proceso PADRE infile: %i\n", node->infile);
	waitpid(pid, NULL, 0);
}

void	execute_nodes(t_cmd **nodes, t_shell *shell)
{
	t_cmd	*node;

	node = *nodes;
	while (node)
	{
		printf("Tiene next\n");
		fork_child(node, shell);
		node = node->next;
	}
}
