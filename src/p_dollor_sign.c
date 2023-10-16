#include "minishell.h"

int	varible_search(t_list *env_lst, char **var, int flag)
{
	if (env_lst == NULL)
		return (1);  // Env list is empty
	while (env_lst->next != NULL && flag == 0)
	{
		if (strcmp(*var, env_lst->key) == 0)
		{
			free(*var); // Free the old
			*var = strdup(env_lst->value); // Set a new value
			return (0);
		}
		env_lst = env_lst->next;
	}
	return (0);
}

char	*after_dolor_sign(t_shell *shell, char *str, int i)
{
	int		start;
	char	*var;
	int		flag;

	start = i;
	flag = 0;
	if (str[i] == ' ' || str[i] == '\0')
	{
		var = ft_strdup("$");
		return (var);
	}
	if (str[i] >= '0' && str[i] <= '9')
	{
		i++;
		start++;
		flag = 1;
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var = ft_substr(str, start, i - start);
	varible_search(shell->env_lst, &var, flag);
	return (var);
}

char	*str_after_var(char *str, int pos)
{
	char	*str_end;

	while (str[pos] && (ft_isalnum(str[pos]) != 0 || str[pos] == '_'))
		pos++;
	str_end = ft_substr(str, pos, ft_strlen(str) - pos + 1);
	return (str_end);
}

char	*ft_concat(char *str, char *var, char *str_end, int *pos)
{
	char	*before_str;
	char	*new_str;
	char	*new_token;

	before_str = ft_strndup((const char *)str, (size_t)*pos);
	new_str = ft_strjoin(before_str, var);
	*pos = ft_strlen(new_str);
	free(before_str);
	free(var);
	new_token = ft_strjoin(new_str, str_end);
	free(new_str);
	free(str_end);
	free(str);
	return (new_token);
}

void	ft_token_check(t_shell *shell, char *str, int i)
{
	int		j;
	char	*str_end;
	char	*var;

	str = shell->tokens[i];
	j = 0;
	while (shell->tokens[i][j])
	{
		if (shell->tokens[i][j] == '$')
		{
			str_end = str_after_var(shell->tokens[i], j + 1);
			var = after_dolor_sign(shell, shell->tokens[i], j + 1);
			if (var)
				shell->tokens[i] = ft_concat(shell->tokens[i], var, str_end, &j);
			else
				printf("Error: var");
		}
		j++;
	}
}