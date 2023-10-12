/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/12 13:15:47 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

void	parse_env(t_shell *shell, char **envp)
{
	shell->env_copy = ft_strddup((const char **)envp);
	create_env_lst(shell, envp);
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**tokens;
	t_shell	*shell;
	int		mode;
	int		i;

	if (argc > 1)
		mini_args(argc, argv, &mode);
	shell = malloc(sizeof(t_shell));
	atexit(ft_leaks);
	printf("\n\nUSER is: @%s\n", getenv("USER"));
	parse_env(shell, envp);
	while (1)
	{
		input = readline("minishell> ");
		if (!input || !ft_strcmp(input, "exit")) // si usario hace un click a ctrl + d significa que readline ha devuelto NULL
			break ; // exit shell
			
		if (strcmp(input, "env") == 0)
			print_env_variables(shell->env_lst_copy);
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			tokens = p_split(input);
			printf("added to history: %s\n", input);
			free(input);
		}
		dbg_print_array_tokens(tokens, mode);
	}
	free_params(shell);
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	//free (input);
	return (0);
}
