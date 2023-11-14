#include "minishell.h"

void	put_token(t_shell *shell, int i, t_cmd *new_node)
{
	if (is_argument(shell->tokens[i]))
		add_argument(shell, shell->tokens[i], new_node);
	else
		check_redir(new_node, &i, shell, 0);
}

int	type_three(t_shell *shell, int *i)
{
	if (assign_type(shell->tokens[*i][0]) == 3)
	{
		*i = *i + 1;
		return (1);
	}
	return (0);
}
