#include "minishell.h"

void	varible_search(t_shell *env_lst, char *var)
{
	int	i;

	i = 0;
	while (env_lst[i])
	{
		if (strcmp(var, env_lst->key) == 0)
		{
			free(var); // Free the old
			&var = strdup(env_lst->value); // Set a new value
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_end(char *str, int pos)
{
	pos++;
	while (str[pos])
	{
		if (str[pos] == 34)
			return (0);
		pos++;
	}
	printf("error\n");
	exit (1);
}

char	*after_dolor_sign(t_shell *shell, char *str, int i)
{
	int		j;
	int		save;
	char	*var;

	i++;
	save = i;
	j = 0;
	while (str[i])
	{
		if (!(str[i] > 47 && str[i] < 58) || !(str[i] > 64 && str[i] < 91)
			|| !(str[i] > 96 && str[i] < 123) || !str[i] == 95)
				break ;
		i++;
	}
	var = malloc(sizeof(char) * (i - save));
	i = save;
	while (i - save > count)
	{
		var[j] = str[i];
		i++;
		j++;
	}
	var[j] = '\0';
	if (varible_search(shell->env_lst, &var) == 0)
		return (var);
	else
		return NULL;
}

char	*ft_concat(char *str, char *var, char *str_end, int *pos)
{
	char	*before_str = ft_strndup((const char *)str, pos)
	int		before_var_len = strlen(before_str);
	char	*new_str = ft_strjoin(before_str, var);
	&pos = ft_strlen(new_str);
	free(before_str);
	free(var);
	char *new_token = ft_strjoin(new_str, str_end);
	free(str);
	return (new_token);
}

char	*str_after_var(char *str, int pos)
{
	char	*str_end;

	pos++;
	while (str[pos])
	{
		if (!(str[pos] > 47 && str[pos] < 58) || !(str[pos] > 64 && str[pos] < 91)
			|| !(str[pos] > 96 && str[pos] < 123) || !str[pos] == 95)
				break ;
		pos++;
	}
	str_end = ft_substr(str, pos, ft_strlen(str) - pos);
	return (str_end);
}

// to detect "$" character in a token
void	ft_token_check(t_shell *shell)
{
	int		i;
	int		j;
	char	*var = NULL;
	char	*str_end = NULL;

	i = 0;
	while (shell->tokens[i])
	{
		j = 0;
		while (shell->tokens[i][j])
		{
			if (shell->tokens[i][j] == 34 && shell->tokens[i][j + 1] != 34 && check_end(shell->tokens[i], j) != 1)
			{
				while (shell->tokens[i][j])
				{
					j++;
					if (ft_strchr(token[i], '$') != NULL)
					{
						str_end = str_after_var(shell->tokens[i], j);
						var = after_dolor_sign(shell, shell->tokens[i], j);
						if (var)
						{
							shell->tokens[i] = ft_concat(shell->tokens[i], var, str_end, *j);
							break ;
						}
						else
							printf("not found\n")
					}
				}
			}
			j++;
		}
		i++;
	}
}
