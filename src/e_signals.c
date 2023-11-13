#include "minishell.h"

void	is_sigint(void)
{
	if (shell_state == 1)
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		write(1, "\033[K\n", 5);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
	}
	else
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
	}
}

void	is_sigquit(void)
{
	if (shell_state)
		ft_printf("\nPresionado Ctrl+\\ en interactivo\n");
	else
		ft_printf("\nPresionado Ctrl+\\ (SIGQUIT) durante una 0tarea\n");
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
		is_sigint();
	else if (signal == SIGQUIT)
		is_sigquit();
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
	//sigemptyset(&sa->sa_mask);
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
}
