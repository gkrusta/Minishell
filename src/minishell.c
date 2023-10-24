/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/24 16:02:41 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	zero(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < 50)
	{
		shell->space_next[i] = '0';
		i++;
	}
}

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
	shell->exit_status = 0;
	atexit(ft_leaks);
	printf("\n\nUSER is: @%s\n", getenv("USER"));
	parse_env(shell, envp);
	shell->space_next = ft_calloc(50, sizeof(char));
	while (1)
	{
		zero(shell);
		input = readline("minishell> ");
		if (!input || !ft_strcmp(input, "exit")) // si usario hace un click a ctrl + d significa que readline ha devuelto NULL
			break ; // exit shell
		if (ft_strcmp(input, "env") == 0)
			print_env_variables(shell, shell->env_lst);
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			shell->tokens = p_split(input, shell);
			//ft_trim(shell);
			dbg_print_array_tokens(shell->tokens, mode, shell);
			printf("added to history: %s\n", input);
			if (strcmp(shell->tokens[0], "export") == 0)
				export(shell, &shell->tokens[1]);
			if (strcmp(shell->tokens[0], "echo") == 0)
				echo(shell, &shell->tokens[1]);
			if (strcmp(shell->tokens[0], "cd") == 0)
				cd(shell, &shell->tokens[1]);
			if (strcmp(shell->tokens[0], "unset") == 0)
				unset(shell, &shell->tokens[1]);
			if (strcmp(shell->tokens[0], "pwd") == 0)
				pwd(shell);
			free(input);
			free_tokens(shell);
		}
	}
	free(shell->space_next);
	free_params(shell);
	free (input);
	return (0);
}
