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
	i = 0;
	while (node->args[i])
		i++;
	execve(node->cmd_path, node->args, shell->env);
}

void	fork_child(t_cmd *node, t_shell *shell)
{
	pid_t	pid;

	if (!is_built_in(node->cmd))
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(node->outfile, STDOUT_FILENO);
			exec_comm(node, shell);
		}
		waitpid(pid, NULL, 0);
	}
	dup2((node->outfile - 1), STDIN_FILENO);
	close(node->outfile);
	close((node->outfile - 1));
}

void	execute_nodes(t_cmd **nodes, t_shell *shell)
{
	t_cmd	*node;
	int		stdincpy;
	int		stdoutcpy;

	stdincpy = dup(STDIN_FILENO);
	stdoutcpy = dup(STDOUT_FILENO);
	node = *nodes;
	dup2(node->infile, STDIN_FILENO);
	close(node->infile);
	while (node)
	{
		fork_child(node, shell);
		node = node->next;
	}
	dup2(stdincpy, STDIN_FILENO);
	dup2(stdoutcpy, STDOUT_FILENO);
	close(stdincpy);
	close(stdoutcpy);
}
