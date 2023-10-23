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
		if (node->infile != 0)
		{
			dup2(node->infile, STDIN_FILENO);
			close(node->infile);
		}
		if (node->outfile != 1)
		{
			dup2(node->outfile, STDOUT_FILENO);
			close(node->outfile);
		}
		exec_comm(node, shell);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (node->infile != 0)
			close(node->infile);
		if (node->outfile != 1)
		{
			dup2(node->outfile, STDOUT_FILENO);
			close(node->outfile);
		}
	}
}

void	execute_nodes(t_cmd **nodes, t_shell *shell)
{
	t_cmd	*node;

	node = *nodes;
	while (node)
	{
		fork_child(node, shell);
		node = node->next;
	}
}
