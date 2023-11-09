/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:39:58 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/09 17:39:40 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell *shell, int end, long i, char *args, char *error_msg)
{
	shell->exit_status = i % 256;
	printf("exit\nminishell: exit: %s: %s:\n", args, error_msg);
	if (end)
	{
		free(shell->space_next);
		free_params(shell);
		exit(shell->exit_status);
	}
	else
		return (shell->exit_status);
}

int	various_args(t_shell *shell, char **args, int i)
{
	int		j;
	char	*error_msg;

	j = 0;
	error_msg = NULL;
	while (args[i])
	{
		while (args[i][j])
		{
			if (i > 1)
			{
				ft_exit(shell, 0, 1, args[i], "too many arguments");
				return (shell->exit_status);
			}
			if (!ft_isdigit(args[i][j]) && i == 1)
				ft_exit(shell, 1, 255, args[i], ": numeric argument required");
			j++;
		}
		i++;
	}
	return (0);
}

void	exit_minishell(t_shell *shell, char **args)
{
	long	i;

	i = 0;
	if (args[1] == NULL)
	{
		shell->exit_status = 0;
		exit(0);
	}
	if (args[1] != NULL)
	{
		i = ft_long_atoi(args[1]);
		shell->exit_status = i % 256;
		free(shell->space_next);
		free_params(shell);
		exit(shell->exit_status);
	}
	else
		various_args(shell, args, i);
}
