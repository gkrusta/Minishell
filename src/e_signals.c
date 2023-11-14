/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:25:23 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/14 10:44:17 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_sigint(void)
{
	if (g_shell_state == 1 || g_shell_state == 4)
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		write(1, "\033[K\n", 5);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		g_shell_state = 4;
	}
	else
	{
		g_shell_state = 3;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
	}
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
		is_sigint();
	else if (signal == EOF)
	{
		if (g_shell_state)
			ft_printf("\nPresionado Ctrl+D en interactivo\n");
		else
			ft_printf("\nPresionado Ctrl+D durante una tarea\n");
	}
}

void	setup_signal_handling(struct sigaction *sa)
{
	sa->sa_handler = signal_handler;
	sa->sa_flags = 0;
	sa->sa_mask = 0;
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
}
