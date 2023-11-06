/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:14:43 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/02 14:08:25 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_shell *shell, char **tokens, int i)
{
	if (shell->space_next[i - 1] == '1' && tokens[i + 1] != NULL)
		printf("%s ", tokens[i]);
	else
		printf("%s", tokens[i]);
}

int	echo(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	//printf("args %s    %d\n", args[0], i);
	if (args[i] == NULL)
	{
		ft_printf("/0");
		return (0);
	}
	if (ft_strcmp(args[i], "-n") == 0)
		i++;
	ft_trim(shell);
	args = shell->tokens;
	i++;
	//printf("args seccond time %s    %d\n", args[i], i);
	while (args[i])
	{
		if (ft_strcmp(args[i], "$") == 0)
			printf("$");
		else if (ft_strcmp(args[i], "$?") == 0)
		{
			printf("%d", shell->exit_status);
			if (args[i + 1] != NULL)
				printf(" ");
			shell->exit_status = 0;
		}
		else if (!(ft_strcmp(args[i], "$") == 0))
			print_echo(shell, args, i);
		i++;
	}
	if (!(ft_strcmp(shell->tokens[1], "-n") == 0))
	{
		//printf("here %s", shell->tokens[1]);
		printf("\n");
	}
	shell->exit_status = 0;
	return (0);
}
