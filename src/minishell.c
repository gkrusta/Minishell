/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvilchez <pvilchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/13 14:55:03 by pvilchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_state;

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

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

void	ft_init(t_shell *shell)
{
	shell->env = NULL;
	shell->env_lst = NULL;
	shell->tokens = NULL;
	shell->exit_status = 0;
	shell->space_next = NULL;
	shell->lvl = 1;
	shell->fd_in = 0;
	shell->stdincpy = 0;
	shell->stdoutcpy = 0;
}

/* void	final_cleanup()
{
	
} */

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	t_shell				*shell;
	int					mode;
	struct sigaction	sa;

	setup_signal_handling(&sa);
	input = NULL;
	if (argc > 1)
		mini_args(argc, argv, &mode);
	shell = malloc(sizeof(t_shell));
	ft_init(shell);
	atexit(ft_leaks);
	printf("\n\nUSER is: @%s\n", getenv("USER"));
	parse_env(shell, envp);
	shell->space_next = ft_calloc(50, sizeof(char));
	while (1)
	{
		zero(shell);
		shell_state = 1;
		input = readline("minishell> ");
		shell_state = 0;
		if (!input/*  || !ft_strcmp(input, "exit") */)
			break ;
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			p_split(input, shell);
			dbg_print_array_tokens(shell->tokens, mode, shell);
			ft_trim_tokens(shell);
			dbg_print_array_tokens(shell->tokens, mode, shell);
			make_nodes(shell, input, mode);
		}
		else
			free(input);
	}
	if (input)
		free (input);
	free(shell->space_next);
	free_params(shell);
	return (0);
}
