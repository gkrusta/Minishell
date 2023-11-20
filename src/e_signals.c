/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:25:23 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/20 18:10:41 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_interactive(void)
{
	rl_on_new_line();
	if (g_shell_state == 2)
		write(1, "> ", 2);
	rl_redisplay();
	write(1, "\033[K\n", 5);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_shell_state = 4;
}

void	is_sigint(int signal)
{
	(void)signal;
	if (g_shell_state == 1 || g_shell_state == 4 || g_shell_state == 2)
		signal_interactive();
	else if (g_shell_state == 5)
	{
		g_shell_state = 3;
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else
	{
		g_shell_state = 3;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	setup_signal_handling(void)
{
	signal(SIGINT, is_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
