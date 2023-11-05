#include "minishell.h"

void	solve_quotes(int *q, char *c)
{
	if (*q == 0)
	{
		*q = 2 - (*c % 2);
		c[0] = '\0';
	}
	else if ((*q == 1 && *c == 39) || (*q == 2 && *c == 34))
	{
		*q = 0;
		c[0] = '\0';
	}
}

char	*add_char(char *new_token, char *c, int *j)
{
	char	*aux;

	aux = new_token;
	new_token = ft_strjoin(aux, c);
	*j = *j + 1;
	free(aux);
	return (new_token);
}

void	change_token_value(char *new_token, t_shell *shell, int *i)
{
	free(shell->tokens[*i]);
	shell->tokens[*i] = new_token;
	*i = *i + 1;
}

void	ft_trim_tokens(t_shell *shell)
{
	int		i;
	int		j;
	int		quotes;
	char	*new_token;
	char	*c;

	i = 0;
	while (shell->tokens[i])
	{
		new_token = ft_calloc(1, sizeof(char));
		quotes = 0;
		j = 0;
		while (shell->tokens[i][j])
		{
			c = ft_calloc(2, sizeof(char));
			c[0] = shell->tokens[i][j];
			if (*c == 39 || *c == 34)
				solve_quotes(&quotes, c);
			if (*c == '$' && quotes != 1)
				c = find_var(shell, c, &shell->tokens[i][j], &j);
			new_token = add_char(new_token, c, &j);
			free(c);
		}
		change_token_value(new_token, shell, &i);
	}
}
