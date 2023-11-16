/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:25:23 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/15 13:53:36 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_sigint(int signal)
{
	//printf("shel state %d  ", g_shell_state);
	(void)signal;
	if (g_shell_state == 1 || g_shell_state == 4 || g_shell_state == 6)
	{
		rl_on_new_line();
		if (g_shell_state == 6)
			write(1, "> ", 2);
		rl_redisplay();
		write(1, "\033[K\n", 5);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_shell_state = 4;
	}
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
