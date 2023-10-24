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

void	execute_nodes(t_cmd *node, t_shell *shell)
{
	int	i;
	int	fd[2];

    int prevRead = 0; // Descriptor de archivo de lectura previo
	i = 0;
	while (node)
	{
		if (fork() == 0)
		{
			if (i > 0)
			{
				dup2(prevRead, 0);
				close(prevRead);
			}
			if (i < numPipes - 1)
			{
				dup2(fd[1], 1);
				close(fd[1]);
			}
			exec_comm(node, shell);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			close(fd[1]);
			prevRead = fd[0];
		}
		node = node->next;
		i++;
	}
}





/*
void	fork_child(t_cmd *node, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (node->infile != 0)
			close(node->infile);
		dup2(node->outfile, STDOUT_FILENO);
		exec_comm(node, shell);
	}
	waitpid(pid, NULL, 0);
	if (node->outfile != 1)
		close(node->outfile);
	dup2(node->outfile - 1, STDIN_FILENO);
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
*/