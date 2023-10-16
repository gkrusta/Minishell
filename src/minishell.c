/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvilchez <pvilchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/16 16:20:21 by pvilchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env(t_shell *shell, char **envp)
{
	shell->env = ft_strddup((const char **)envp);
	create_env_lst(shell, envp);
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;
	int		mode;

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
			print_env_variables(shell->env_lst);
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			shell->tokens = p_split(input);
			ft_trim(shell);
			dbg_print_array_tokens(shell->tokens, mode);
			printf("added to history: %s\n", input);
			free(input);
			if (strcmp(shell->tokens[0], "export") == 0)
				export(shell, &shell->tokens[1]);
			if (strcmp(shell->tokens[0], "unset") == 0)
				unset(shell, &shell->tokens[1]);
			free_tokens(shell);
		}
	}
	free_params(shell);
	free (input);
	return (0);
}
