/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvilchez <pvilchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/12 18:28:08 by pvilchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	ft_leaks(void)
{
	system("leaks -q minishell");
} */

void	parse_env(t_shell *shell, char **envp)
{
	shell->env = ft_strddup((const char **)envp);
	create_env_lst(shell, envp);
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
