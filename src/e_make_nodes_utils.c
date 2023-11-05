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

void	check_redir(t_cmd *node, int *i, t_shell *shell, int plus)
{
	int		fd[2];

	pipe(fd);
	if (shell->fd_in != 0)
	{
		node->infile = shell->fd_in;
		shell->fd_in = 0;
	}
	if (ft_strcmp(shell->tokens[*i], "|") == 0)
		token_pipe(node, fd, shell);
	else if (ft_strcmp(shell->tokens[*i], "<") == 0)
		token_input(shell->tokens, i, node);
	else if (ft_strcmp(shell->tokens[*i], ">") == 0)
		token_output(shell->tokens, i, node);
	else if (ft_strcmp(shell->tokens[*i], ">>") == 0)
		token_output_cat(shell->tokens, i, node);
	else if (ft_strcmp(shell->tokens[*i], "<<") == 0)
		token_heredoc(shell->tokens, i, node);
	*i = *i + plus;
}

char	*str_change_value(char *old_str, char *new_str)
{
	free(old_str);
	old_str = new_str;
	return (new_str);
}

void	init_values(t_shell *shell, int *i)
{
	*i = 0;
	shell->fd_in = 0;
}

