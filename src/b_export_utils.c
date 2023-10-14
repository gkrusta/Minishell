#include "minishell.h"

void	free_arg(char *arg_key, char *arg_value)
{
	if (arg_key)
		free(arg_key);
	if (arg_value)
		free(arg_value);
}

void	sort_array(char **str_array, int lst_size)
{
	int		i;
	char	*aux;

	i = 0;
	aux = NULL;
	while (i < lst_size && str_array[i + 1])
	{
		if (ft_strcmp(str_array[i], str_array[i + 1]) > 0)
		{
			aux = str_array[i];
			str_array[i] = str_array[i + 1];
			str_array[i + 1] = aux;
			i = 0;
		}
		else
			i++;
	}
}

char	*write_line(char *str1, char *str2, int len)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	res = ft_calloc(len, sizeof(char));
	while (str1[i])
	{
		res[i] = str1[i];
		i++;
	}
	res[i] = '=';
	res[i + 1] = '"';
	i += 2;
	j = 0;
	while (str2[j])
	{
		res[i] = str2[j];
		j++;
		i++;
	}
	res[i] = '"';
	return (res);
}

char	**fill_str_array(t_list *env_lst, int *lst_size)
{
	char	**str_array;
	int		i;
	int		len;

	i = 0;
	*lst_size = ft_lstsize(env_lst);
	str_array = ft_calloc(*lst_size + 1, sizeof(char *));
	while (i < *lst_size)
	{
		len = (ft_strlen(env_lst->key) + ft_strlen(env_lst->value) + 4);
		str_array[i] = write_line(env_lst->key, env_lst->value, len);
		env_lst = env_lst->next;
		i++;
	}
	return (str_array);
}

void	export_empty(t_shell *shell)
{
	char	**str_array;
	int		i;
	int		lst_size;

	lst_size = 0;
	str_array = fill_str_array(shell->env_lst, &lst_size);
	sort_array(str_array, lst_size);
	i = 0;
	while (str_array[i])
	{
		printf("declare -x %s\n", str_array[i]);
		i++;
	}
	free (str_array);
}
