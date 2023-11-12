#include "minishell.h"

char	*add_env_var(char *new_token, char *value)
{
	char	*joined;

	joined = ft_strjoin(new_token, value);
	free(value);
	return (joined);
}

void	*find_value(t_shell *shell, char *name)
{
	t_list	*aux;

	aux = shell->env_lst;
	while (aux)
	{
		if (ft_strcmp((char *)aux->key, name) == 0)
			return (aux->value);
		aux = aux->next;
	}
	if (ft_isdigit(*name) == 1)
		return (&name[1]);
	else
		return (NULL);
}

char	*capture_key(char *c)
{
	char	*key;
	int		i;

	c++;
	i = 0;
	key = ft_calloc(20, sizeof (char));
	while (c && (ft_isalnum(*c) || *c == '?'))
	{
		key[i] = *c;
		if (key[0] == '?')
			break ;
		i++;
		c++;
	}
	return (key);
}

char	*find_var(t_shell *shell, char *c, char *token, int *j)
{
	char	*key;
	char	*value;

	key = capture_key(token);
	if (key[0] == '?')
	{
		free (c);
		c = ft_itoa(shell->exit_status);
		*j = *j + 1;
	}
	else if (key[0])
	{
		free(c);
		value = (char *)find_value(shell, key);
		printf("value is %s", value);
		if (ft_isdigit(*key) == 1)
			*j = *j + 1;
		*j = *j + ft_strlen(key);
		if (value)
			c = ft_strdup(value);
		else
			c = ft_calloc(1, sizeof (char));
	}
	free(key);
	return (c);
}
