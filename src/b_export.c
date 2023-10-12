#include "minishell.h"

void	copy_value(t_list *env_list, char *arg_value)
{
	char	*aux;
	int		len;

	len = ft_strlen(arg_value);
	aux = env_list->value;
	env_list->value = ft_calloc(len + 1, 1);
	ft_strlcpy(env_list->value, arg_value, len);
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
	printf("\n	antes while\n");
	printf("%s  %s \n", arg_key, env_key();
	while (arg_key[i] && env_key[i] && arg_key[i] == env_key[i])
	{
		i++;
	}
	printf("\n	%i caracteres iguales\n", i);
	if (env_key[i] == '=' || env_key[i] == '\0')
	{
		*found = 1;
		return (1);
	}
	return (0);
}

void	extract_values(char *arg, char *key, char *value)
{
	int	i;
	int	j;

	key = ft_calloc(ft_strlen(arg) + 1, 1);
	value = ft_calloc(ft_strlen(arg) + 1, 1);
	i = 0;
	j = 0;
	while (arg[i] && arg[i] != '=')
	{
		key[i] = arg[i];
		i++;
	}
	if (arg[i] == '=')
		i++;
	while (arg[i])
	{
		value[j] = arg[i];
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
	arg_key = NULL;
	arg_value = NULL;
	while (args[i])
	{
		printf("\n	nuevo argumento\n");
		found = 0;
		env_list = shell->env_lst;
		extract_values(args[i], arg_key, arg_value);
		while (env_list && found == 0)
		{
			printf("\n	    nueva env\n");
			if (key_found(arg_key, env_list->key, &found))
				copy_value(env_list, arg_value);
			env_list = env_list->next;
		}
		if (!found)
			create_key(env_list, arg_key, arg_value);
		free_arg(arg_key, arg_value);
		i++;
	}
}
