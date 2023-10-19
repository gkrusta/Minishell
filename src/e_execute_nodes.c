#include "minishell.h"

void	exec_comm(char *argv, char **envp)
{
	char	**command;
	char	*path;

	command = ft_split(argv, ' ');
	path = find_path(command[0], envp);
	if (!path)
	{
		free_str_list(command);
		error("Path error");
	}
	if (execve(path, command, envp) == -1)
		error("Error during execution");
}

void	fork_child(t_cmd *node)
{
	pid_t	pid;

	pid = fork();
	dup2(node->infile, STDIN_FILENO);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exec_comm(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	execute_nodes(t_cmd **nodes)
{
	t_cmd	*node;

	node = *nodes;
	while (node)
	{
		fork_child(node);
		dup2(fileout, STDOUT_FILENO);
		exec_comm(argv[argc - 2], envp);
		node = node->next;
	}
}
