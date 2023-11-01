/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/01 20:22:14 by gkrusta          ###   ########.fr       */
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


char	*check_level(char *lvl)
{
	int		level;
	char	*result;
	int		i;

	i = 0;
	while (lvl[i])
	{
		if (ft_isdigit(lvl[i]) == 0)
		{
			lvl = ft_strdup("1");
			return (lvl); 
		}
		i++;
	}
	level = ft_atoi(lvl);
	level += 1;
	result = ft_itoa(level);
	return (result);
}

void	update_level(t_shell *shell, int flag)
{
	char	**lvl;
	t_list	*aux;

	if (flag == 1 && key_search(shell->env_lst, "SHLVL") == 1)
	{
		lvl = ft_calloc(2, sizeof(char *));
		lvl[0] = ft_strdup("SHLVL=1");
		export(shell, lvl);
	}
	else if (flag == 1 && key_search(shell->env_lst, "SHLVL") == 0)
	{
		lvl = ft_calloc(3, sizeof(char *));
		aux = node_search(shell->env_lst, "SHLVL");
		lvl[0] = check_level(aux->value);
		lvl[1] = ft_strjoin("SHLVL=", lvl[0]);
		printf("new level    %s\n", lvl[0]);
		if (lvl[0] != NULL && lvl[1] != NULL)
			export(shell, &lvl[1]);
		free_args(lvl);
	}
	update_env(shell);
	//printf("here %s\n", shell->env)
}

void	parse_env(t_shell *shell, char **envp)
{
/* 	static int	entry_count;

	entry_count = 0;
	entry_count += 1;
	if (entry_count == 1) */
	shell->env = ft_strddup((const char **)envp);
/* 	else if (entry_count > 1)
		update_level(shell, 1); */
	create_env_lst(shell, envp);
}

/* void	ft_leaks(void)
{
	system("leaks -q minishell");
} */

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;
	int		mode;

	setup_signal_handling();
	input = NULL;
	if (argc > 1)
		mini_args(argc, argv, &mode);
	shell = malloc(sizeof(t_shell));
	shell->exit_status = 0;
	//atexit(ft_leaks);
	printf("\n\nUSER is: @%s\n", getenv("USER"));
	parse_env(shell, envp);
	shell->space_next = ft_calloc(50, sizeof(char));
	while (1)
	{
		zero(shell);
		shell_state = 1;
		input = readline("minishell> ");
		shell_state = 0;
		if (!ft_strcmp(input, "exit"))
			break ;
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			shell->tokens = p_split(input, shell);
			dbg_print_array_tokens(shell->tokens, mode, shell);
			make_nodes(shell, input, mode);
		}
	}
	free(shell->space_next);
	free_params(shell);
	free (input);
	return (0);
}
