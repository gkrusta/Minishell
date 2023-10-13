/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/13 13:29:45 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void ft_leaks(void)
{
	system("leaks -q minishell");
} */

int main(int argc, char **argv, char **env)
{
	char	*input;
	char	*username;
	char	**tokens;
	int		i;

	(void)argc;
	(void)argv;
	//atexit(ft_leaks);
	username = getenv("USER");
	printf("\n\nUSER is: @%s\n", username); 
	while (1)
	{
		input = readline("minishell> ");
		if (!input) // si usario hace un click a ctrl + d significa que readline ha devuelto NULL
		{
			printf("\n");
			break ; // exit shell
		}
		if (strcmp(input, "env") == 0) // imprime el path
		{
			i = 0;
			while (env[i])
			{
				printf("%s\n", env[i]);
				i++;
			}
		}
		if (strcmp(input, "test") == 0)
			ft_token_check(tokens);
		printf("added to history: %s\n", input);
		dbg_print_array_tokens(tokens);
		free(input);
	}
	return (0);
}
