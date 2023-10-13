/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/13 13:30:11 by gkrusta          ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;
	int		mode;
	char	**pablo;

	pablo = calloc(3, sizeof(char *));
	pablo[0] = "123=yyy";
	pablo[1] = "abc";
	pablo[2] = NULL;

	if (argc > 1)
		mini_args(argc, argv, &mode);
	shell = malloc(sizeof(t_shell));
	//atexit(ft_leaks);
	printf("\n\nUSER is: @%s\n", getenv("USER"));
	parse_env(shell, envp);
	while (1)
	{
		input = readline("minishell> ");
		if (!input || !ft_strcmp(input, "exit")) // si usario hace un click a ctrl + d significa que readline ha devuelto NULL
			break ; // exit shell
		if (strcmp(input, "env") == 0)
			print_env_variables(shell->env_lst);
		if (strcmp(input, "export") == 0)
			export(shell, pablo);
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			shell->tokens = p_split(input);
			dbg_print_array_tokens(shell->tokens, mode);
			free_tokens(shell);
			printf("added to history: %s\n", input);
			free(input);
		}
	}
	free_params(shell);
	//free (input);
	return (0);
}
