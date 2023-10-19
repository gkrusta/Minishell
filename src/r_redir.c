#include "minishell.h"

void	token_pipe(t_cmd *node, int *fd, int *fd_in)
{
	node->outfile = fd[0];
	*fd_in = fd[1];
}

void	token_input(char **tokens, int *i, t_cmd *node)
{
	int	fd_read;

	if (tokens[*i + 1])
	{
		fd_read = open(tokens[*i +1], O_RDONLY, 0777);
		node->infile = fd_read;
		*i = *i + 1;
	}
}
