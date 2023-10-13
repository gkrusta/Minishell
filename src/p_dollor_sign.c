#include "minishell.h"

int	varible_search(t_list *env_lst, char **var)
{
	if (env_lst == NULL)
		return 1;  // Env list is empty
	while (env_lst->next != NULL)
	{
		if (strcmp(*var, env_lst->key) == 0)
		{
			free(*var); // Free the old
			*var = strdup(env_lst->value); // Set a new value
			return (0);
		}
		env_lst = env_lst->next;
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

/* char	*after_dolor_sign(t_shell *shell, char *str, int i)
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
			|| !(str[i] > 96 && str[i] < 123) || !(str[i] == 95))
				break ;
		i++;
	}
	var = malloc(sizeof(char) * (i - save + 1));
	i = save;
	while (save > j)
	{
		var[j] = str[i];
		i++;
		j++;
		save--;
	}
	var[j] = '\0';
	printf("!!!!!!!!!! value at the begging is %s\n", var);
	if (varible_search(shell->env_lst, &var) == 0)
	{
		//printf("shit explodes\n");
		return (var);
	}
	else
		return NULL;
} */

char	*after_dolor_sign(t_shell *shell, char *str, int i)
{
	int j = i;

	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_')) {
		j++;
	}
	char *var = ft_substr(str, i, j - i);
	//printf("!!!!!!!!!! value at the begging is %s\n", var);
	if (varible_search(shell->env_lst, &var) == 0)
	{
		//printf("var after dup is %s\n", var);
		return (var);
	}
	else
	{
		free(var);
		return NULL;
	}
}

char	*str_after_var(char *str, int pos)
{
	char	*str_end;

	//pos++;
	while (str[pos] && (ft_isalnum(str[pos]) != 0 || str[pos] == '_'))
	{
		pos++;
	}
	str_end = ft_substr(str, pos, ft_strlen(str) - pos + 1);
	return (str_end);
}

// to detect "$" character in a token
/* void	ft_token_check(t_shell *shell)
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
					if (ft_strchr(shell->tokens[i], '$') != NULL)
					{
						str_end = str_after_var(shell->tokens[i], j);
						//printf("shit explodes\n");
						var = after_dolor_sign(shell, shell->tokens[i], j);
						if (var)
						{
							shell->tokens[i] = ft_concat(shell->tokens[i], var, str_end, &j);
							break ;
						}
						else
							printf("not found\n");
					}
				}
			}
			j++;
		}
		i++;
	}
} */
/* char *ft_concat(char *str, char *var, char *str_end)
{
	char *new_token = ft_strjoin(str, var);
	new_token = ft_strjoin(new_token, str_end);
	free(str);
	free(var);
	free(str_end);
	return (new_token);
} */
/* 
char	*ft_concat(char *str, char *var, char *str_end, int *pos)
{
	printf("after %s %s str end is: %s\n", str, var, str_end);
	char	*before_str = ft_strndup((const char *)str, (size_t)pos);
	//int		before_var_len = strlen(before_str);
	char	*new_str = ft_strjoin(before_str, var);
	*pos = ft_strlen(new_str);
	free(before_str);
	free(var);
	char *new_token = ft_strjoin(new_str, str_end);
	free(new_str);
	free (str);
	return (new_token);
} */

char	*ft_concat(char *str, char *var, char *str_end, int *pos)
{
	char *before_str = ft_strndup((const char *)str, (size_t)(*pos));
	char *new_str = ft_strjoin(before_str, var);
	free(before_str);
	char *new_token = ft_strjoin(new_str, str_end);
	free(str);
	free(var);
	free(str_end);
	*pos = ft_strlen(new_token);
	return (new_token);
}


// Modify your ft_token_check function as follows:
void ft_token_check(t_shell *shell)
{
	int i = 0;

	while (shell->tokens[i])
	{
		int j = 0;
		while (shell->tokens[i][j])
		{
			printf("12\n");
			if (shell->tokens[i][j] == '$' && shell->tokens[i][j + 1] != '\0')
			{
				char *str_end = str_after_var(shell->tokens[i], j + 1);
				printf("str_end is %s\n", str_end);
				char *var = after_dolor_sign(shell, shell->tokens[i], j + 1);
				if (var)
				{
					printf("before %s\n", shell->tokens[i]);
					shell->tokens[i] = ft_concat(shell->tokens[i], var, str_end, &j);
					printf("after %s\n", shell->tokens[i]);
					break ;
				}
				else
				{
					printf("!!\n");
					j += ft_strlen(str_end) - 1;
				}
			}
			j++;
		}
		i++;
	}
}
