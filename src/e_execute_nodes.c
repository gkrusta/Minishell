#include "minishell.h"

void	exec_built(t_cmd *node, t_shell *shell, int stdoutcpy)
{
	dup2(node->outfile, STDOUT_FILENO);
	if (ft_strcmp(node->cmd, "env") == 0)
		print_env_variables(shell, shell->env_lst);
	if (strcmp(node->cmd, "export") == 0)
		export(shell, node->args);
	if (strcmp(node->cmd, "echo") == 0)
		echo(shell, node->args);
	if (strcmp(node->cmd, "cd") == 0)
		cd(shell, node->args);
	if (strcmp(node->cmd, "unset") == 0)
		unset(shell, node->args);
	if (strcmp(node->cmd, "pwd") == 0)
		pwd(shell);
	close(node->outfile);
	dup2(stdoutcpy, STDOUT_FILENO);
	dup2((node->outfile - 1), STDIN_FILENO);
	close((node->outfile - 1));
}

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

	pid = fork();
	if (pid == 0)
	{
		dup2(node->outfile, STDOUT_FILENO);
		exec_comm(node, shell);
	}
	waitpid(pid, NULL, 0);
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
		if (is_built_in(node->cmd))
			exec_built(node, shell, stdoutcpy);
		else if (node->cmd_path[0] == '\0')
		{
			dup2(stdoutcpy, STDOUT_FILENO);
			if (node->cmd[0] == '\0')
				printf("%s: command not found\n", node->args[0]);
			else
				printf("%s: command not found\n", node->cmd);
			break ;
		}
		else
			fork_child(node, shell);
		node = node->next;
	}
	dup2(stdincpy, STDIN_FILENO);
	dup2(stdoutcpy, STDOUT_FILENO);
	close(stdincpy);
	close(stdoutcpy);
}
