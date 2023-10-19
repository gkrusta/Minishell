#include "minishell.h"

int	is_built_in(char *token)
{
	if (ft_strcmp(token, "env") == 0)
		return (1);
	else if (ft_strcmp(token, "export") == 0)
		return (1);
	else if (ft_strcmp(token, "unset") == 0)
		return (1);
	else if (ft_strcmp(token, "cd") == 0)
		return (1);
	else if (ft_strcmp(token, "echo") == 0)
		return (1);
	else if (ft_strcmp(token, "pwd") == 0)
		return (1);
	else if (ft_strcmp(token, "exit") == 0)
		return (1);
	return (0);
}

void	check_redir(t_cmd *node, char **tokens, int *i, int *fd_in)
{
	int		fd[2];

	pipe(fd);
	if (*fd_in != 0)
	{
		node->infile = *fd_in;
		*fd_in = 0;
	}
	if (ft_strcmp(tokens[*i], "|") == 0)
		token_pipe(node, fd, fd_in);
	else if (ft_strcmp(tokens[*i], "<") == 0)
		token_input(tokens, i, node);
}
