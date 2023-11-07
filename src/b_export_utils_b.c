#include "minishell.h"

void	launch_key_error(t_shell *shell, char *cmd, char *key)
{
	ft_printf("minishell: %s: `%s': invalid identifier\n", cmd, key);
	shell->exit_status = 1;
}

int	check_key(char *key, int print, t_shell *shell, char *cmd)
{
	int	i;

	i = 0;
	if (key[0] && (key[0] == '_' || ft_isalpha(key[0])))
	{
		i++;
		while (key[i])
		{
			if (ft_isalnum(key[i]) || key[i] == '_')
				i++;
			else
			{
				if (print == 1)
					launch_key_error(shell, cmd, key);
				return (0);
			}
		}
		return (1);
	}
	if (print == 1)
		launch_key_error(shell, cmd, key);
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