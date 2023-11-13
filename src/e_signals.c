#include "minishell.h"

void	is_sigint(void)
{
	if (shell_state == 1 || shell_state == 4)
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		write(1, "\033[K\n", 5);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		shell_state = 4;
	}
	else
	{
		shell_state = 3;
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
		if (shell_state)
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
