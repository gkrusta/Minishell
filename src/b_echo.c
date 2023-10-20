/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:14:43 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/20 15:13:47 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exit_status(t_shell *shell)
{
	printf("%d\n", shell->exit_status);
}

void	print_echo(char **tokens)
{
	int	i;

	i = 1;
	while (tokens[i])
	{
		if (!(i == 1))
			printf(" ");
		printf("%s", tokens[i]);
		i++;
	}
	if (!(ft_strcmp(tokens[0], "-n") == 0))
		printf("\n");
}

int	echo(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	if (ft_strcmp(args[i], "$?") == 0)
	{
		printf("%d\n", shell->exit_status);
		shell->exit_status = 0;
		return (0);
	}
	ft_trim(shell);
	if (args[i])
	{
		if (ft_strcmp(args[0], "-n") == 0)
			i++;
		if (ft_strcmp(args[i], "$?") == 0)
			check_exit_status(shell);
		if (!(ft_strcmp(args[0], "$?") == 0))
			print_echo(&shell->tokens[i]);
	}
	return (0);
}
