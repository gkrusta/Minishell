/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:14:43 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/02 10:58:48 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_shell *shell, char **tokens, int i)
{
	if (shell->space_next[i + 1] == '1')
		ft_printf("%s ", tokens[i]);
	else
		printf("%s", tokens[i]);
}

int	echo(t_shell *shell, char **args)
{
	int	i;

	i = 1;
	//printf("args %s\n", args[0]);
	if (args[0] == NULL)
	{
		ft_printf("/0");
		return (0);
	}
	if (ft_strcmp(args[0], "$?") == 0)
	{
		ft_printf("%d\n", shell->exit_status);
		shell->exit_status = 0;
		return (0);
	}
	ft_trim(shell);
	args = shell->tokens;
	while (args[i])
	{
		if (ft_strcmp(args[0], "-n") == 0)
			i++;
		else if (ft_strcmp(args[i], "$") == 0)
			ft_printf("$");
		else if (!(ft_strcmp(args[i], "$") == 0))
			print_echo(shell, args, i);
		i++;
	}
	if (!(ft_strcmp(shell->tokens[0], "-n") == 0))
		ft_printf("\n");
	shell->exit_status = 1;
	return (0);
}
