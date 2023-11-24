/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/24 13:22:41 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_state;

/* void	ft_leaks(void)
{
	system("leaks -q minishell");
} */

void	final_cleanup(t_shell *shell, char *input)
{
	if (input)
		free (input);
	free(shell->space_next);
	free_params(shell);
}

char	*zero(t_shell *shell)
{
	char	*input;
	int		i;

	i = 0;
	while (i < 50)
	{
		shell->space_next[i] = '0';
		i++;
	}
	shell_state = 1;
	input = readline("minishell> ");
	if (shell_state == 4)
		shell->exit_status = 1;
	shell_state = 0;
	return (input);
}

void	ft_init(t_shell *shell, char **envp)
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
	parse_env(shell, envp);
	shell->space_next = ft_calloc(50, sizeof(char));
	printf("\n\nUSER is: @%s\n", getenv("USER"));
}

void	run_input(char *input, t_shell *shell, int mode)
{
	add_history(input);
	p_split(input, shell);
	dbg_print_array_tokens(shell->tokens, mode, shell);
	ft_trim_tokens(shell);
	dbg_print_array_tokens(shell->tokens, mode, shell);
	make_nodes(shell, input, mode);
}

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	t_shell				*shell;
	int					mode;
	//struct sigaction	sa;

	
	if (argc > 1)
		mini_args(argc, argv, &mode);
	shell = malloc(sizeof(t_shell));
	ft_init(shell, envp);
	//atexit(ft_leaks);
	while (1)
	{
		input = zero(shell);
		if (!input)
			break ;
		if (ft_strlen(input) > 0)
			run_input(input, shell, mode);
		else
			free(input);
	}
	final_cleanup(shell, input);
	return (0);
}
