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
		pos++;
	str_end = ft_substr(str, pos, ft_strlen(str) - pos + 1);
	return (str_end);
}

char	*ft_concat(char *str, char *var, char *str_end, int *pos)
{
	//printf("after %s  var %s    str end is: %s\n", str, var, str_end);
	char	*before_str;
	char	*new_str;
	char *new_token;

	before_str = ft_strndup((const char *)str, (size_t)*pos);
	new_str = ft_strjoin(before_str, var);
	*pos = ft_strlen(new_str);
	free(before_str);
	free(var);
	new_token = ft_strjoin(new_str, str_end);
	free(new_str);
	free(str);
	return (new_token);
}

int is_inside_quotes(char *str, int pos)
{
	int inside_quotes;
	int	i;

	inside_quotes = 0;
	i = 0;
	while  (i < pos)
	{
		if (str[i] == '"')
			inside_quotes = 1;
		i++;
	}
	return (inside_quotes);
}

// Modify your ft_token_check function as follows:
void	ft_token_check(t_shell *shell)
{
	int i = 0;
	int inside_quotes = 0;
	while (shell->tokens[i])
	{
		int j = 0;
		while (shell->tokens[i][j])
		{
			printf("j is %c\n", shell->tokens[i][j]);
			if (shell->tokens[i][j] == '"')
				inside_quotes = 1; // Toggle the flag for double quotes
			else if (shell->tokens[i][j] == '$' && is_inside_quotes(shell->tokens[i], j) == 1)
			{
				char *str_end = str_after_var(shell->tokens[i], j + 1);
				char *var = after_dolor_sign(shell, shell->tokens[i], j + 1);
				if (var)
					shell->tokens[i] = ft_concat(shell->tokens[i], var, str_end, &j);
				else
				{
					printf("!!\n");
					// write '\0'
					j += ft_strlen(str_end) - 1;
				}
			}
			j++;
		}
		i++;
	}
}
