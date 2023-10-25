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
	execve(node->cmd_path, NULL, shell->env);
}

void	fork_child(t_cmd *node, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(node->outfile - 1);
		dup2(node->outfile, STDOUT_FILENO);
		exec_comm(node, shell);
	}
	waitpid(pid, NULL, 0);
	dup2(node->outfile - 1, STDIN_FILENO);
	close(node->outfile - 1);
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
}
