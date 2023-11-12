#include "minishell.h"

void	launch_key_error(t_shell *shell, char *cmd, t_list *arg)
{
	ft_printf("minishell: %s: `%s=%s': invalid identifier\n", cmd, (char *)(arg->key), (char *)(arg->value));
	shell->exit_status = 1;
}

int	check_key(t_list *arg, int print, t_shell *shell, char *cmd)
{
	int	i;

	i = 0;
	if ((((char *)(arg->key))[0]) && (((char *)(arg->key))[0] == '_' || ft_isalpha(((char *)(arg->key))[0])))
	{
		i++;
		while (((char *)(arg->key))[i])
		{
			if (ft_isalnum(((char *)(arg->key))[i]) || ((char *)(arg->key))[i] == '_')
				i++;
			else
			{
				if (print == 1)
					launch_key_error(shell, cmd, arg);
				return (0);
			}
		}
		return (1);
	}
	if (print == 1)
		launch_key_error(shell, cmd, arg);
	else
		shell->exit_status = 1;
	return (0);
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