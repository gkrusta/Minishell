/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/11 16:58:39 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env(t_shell *shell, char **envp)
{
	shell->env_copy = ft_strddup((const char **)envp);
	create_env_lst(shell, envp);
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*username;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	//atexit(ft_leaks);
	username = getenv("USER");
	printf("\n\nUSER is: @%s\n", username); 
	parse_env(shell, envp);
	while (1)
	{
		input = readline("minishell> ");
		if (!input) // si usario hace un click a ctrl + d significa que readline ha devuelto NULL
		{
			printf("\n");
			break ; // exit shell
		}
		if (strcmp(input, "env") == 0)
			print_env_variables(shell->env_lst_copy);
		if (ft_strlen(input) > 0)
			add_history(input);
		printf("added to history: %s\n", input);
		free(input);
	}
	free_params(shell);
	return (0);
}