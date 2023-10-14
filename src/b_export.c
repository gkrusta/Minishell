#include "minishell.h"

void	copy_value(t_list *env_list, char *arg_value)
{
	char	*aux;
	int		len;

	len = ft_strlen(arg_value);
	aux = env_list->value;
	env_list->value = ft_calloc(len + 1, 1);
	ft_strlcpy(env_list->value, arg_value, len + 1);
	free(aux);
}

void	create_key(t_list *env_list, char *key, char *value)
{
	t_list	*new_key;

	new_key = ft_lstnew(key, value);
	ft_lstadd_back(&env_list, new_key);
}

int	key_found(char *arg_key, char *env_key, int *found)
{
	int	i;

	i = 0;
	while (arg_key[i] && env_key[i] && arg_key[i] == env_key[i])
	{
		i++;
	}
	if (env_key[i] == '=' || env_key[i] == '\0')
	{
		*found = 1;
		return (1);
	}
	return (0);
}

void	extract_values(char *arg, char **key, char **value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	key[0] = ft_calloc(ft_strlen(arg) + 1, 1);
	value[0] = ft_calloc(ft_strlen(arg) + 1, 1);
	while (arg[i] && arg[i] != '=')
	{
		key[0][i] = arg[i];
		i++;
	}
	if (arg[i] == '=')
		i++;
	while (arg[i])
	{
		value[0][j] = arg[i];
		i++;
		j++;
	}
}

void	export(t_shell *shell, char **args)
{
	t_list	*env_list;
	int		i;
	int		found;
	char	*arg_key;
	char	*arg_value;

	i = 0;
	while (args[i])
	{
		found = 0;
		env_list = shell->env_lst;
		extract_values(args[i], &arg_key, &arg_value);
		while (env_list && found == 0)
		{
			if (key_found(arg_key, (char *)env_list->key, &found))
				copy_value(env_list, arg_value);
			env_list = env_list->next;
		}
		if (!found)
			create_key(shell->env_lst, arg_key, arg_value);
		free_arg(arg_key, arg_value);
		i++;
	}
	if (i == 0)
		export_empty(shell);
}
