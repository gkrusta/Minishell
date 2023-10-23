/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:14:43 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/23 21:00:26 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_space(char **tokens, int i)
{
	static int	flag;

	//flag = 0;

	if (i == 0)
		flag = 0;
	if (tokens[i + 1] == NULL)
	{
		flag = 0;
		return (1);
	}
	else if (tokens[i][0] == 34 && flag == 0)
	{
		//printf("!!!!");
		flag = 1;
		return (1);
	}
	else if (tokens[i][0] == 34 && flag == 1)
	{
		flag = 1;
		return (1);
	}
	else if (tokens[i][0] == 34 && flag == 1 && tokens[i + 1][0] == 34)
	{
		flag = 0;
		return (1);
	}
	else if (flag == 1 && tokens[i + 1][0] == 34)
	{
		flag = 0;
		return (1);
	}
	return (0);
}

void	print_echo(char **tokens, int i)
{
	static int	flag;

	if (put_space(tokens, i) == 0)
		printf(" ");
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
	//ft_trim(shell);
	if (ft_strcmp(args[0], "$?") == 0)
	{
		printf("%d\n", shell->exit_status);
		shell->exit_status = 0;
		return (0);
	}
	while (args[i])
	{
		if (ft_strcmp(args[0], "-n") == 0)
			i++;
		else if (ft_strcmp(args[i], "$") == 0)
			printf("$");
		else if (!(ft_strcmp(args[i], "$") == 0))
			print_echo(args, i);
		i++;
	}
	if (!(ft_strcmp(shell->tokens[0], "-n") == 0))
		printf("\n");
	return (0);
}
