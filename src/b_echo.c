/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:14:43 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/16 17:55:53 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(char **tokens, int flag)
{
	int	i;

	i = 1;
	if (flag == 1)
		i = 2;
	while (tokens[i])
	{
		printf("%s ", tokens[i]);
		i++;
	}
	if (flag == 0)
		printf("\n");
}

void	echo(t_shell *shell, char **args)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (args[i])
	{
		if (ft_strcmp(args[1], "-n") == 0)
			flag = 1;
		print_echo(&shell->tokens[i], flag);
	}
}
