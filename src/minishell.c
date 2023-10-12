/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvilchez <pvilchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/12 12:39:01 by pvilchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int main(int argc, char **argv, char **env)
{
	char	*input;
	char	**tokens;
	int		i;
	int		mode;

	if (argc > 1)
		mini_args(argc, argv, &mode);
	atexit(ft_leaks);
	printf("\n\nUSER is: @%s\n", getenv("USER"));
	while (1)
	{
		input = readline("minishell> ");
		if (!input || !ft_strcmp(input, "exit")) // si usario hace un click a ctrl + d significa que readline ha devuelto NULL
			break ; // exit shell
			
		if (strcmp(input, "env") == 0) // imprime el path
		{
			i = 0;
			while (env[i])
			{
				printf("%s\n", env[i]);
				i++;
			}
		}
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			tokens = p_split(input);
		}
		printf("added to history: %s\n", input);
		dbg_print_array_tokens(tokens, mode);
		free(input);
	}
	return (0);
}
