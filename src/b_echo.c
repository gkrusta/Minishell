/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:14:43 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/25 14:07:58 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_shell *shell, char **tokens, int i)
{
	if (shell->space_next[i + 1] == '1')
		printf("%s ", tokens[i]);
	else
		printf("%s", tokens[i]);
}

int	echo(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	if (args[0] == NULL)
	{
		printf("/0");
		return (0);
	}
	if (ft_strcmp(args[0], "$?") == 0)
	{
		printf("%d\n", shell->exit_status);
		shell->exit_status = 0;
		return (0);
	}
	ft_trim(shell);
	while (args[i])
	{
		if (ft_strcmp(args[0], "-n") == 0)
			i++;
		else if (ft_strcmp(args[i], "$") == 0)
			printf("$");
		else if (!(ft_strcmp(args[i], "$") == 0))
			print_echo(shell, args, i);
		i++;
	}
	if (!(ft_strcmp(shell->tokens[0], "-n") == 0))
		printf("\n");
	shell->exit_status = 1;
	return (0);
}
