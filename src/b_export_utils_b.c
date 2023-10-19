#include "minishell.h"

int	check_key(char *key, int print, t_shell *shell)
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
				{
					ft_printf("minishell: export: '%s'", key);
					ft_printf(": invalid identifier\n");
					shell->exit_status = 1;
				}
				return (0);
			}
		}
		return (1);
	}
	if (print == 1)
	{
		ft_printf("minishell: export: '%s': invalid identifier\n", key);
		shell->exit_status = 1;
	}
	return (0);
}
