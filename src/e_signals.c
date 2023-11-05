#include "minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (shell_state)
			ft_printf("\nminishell> ");
		else
			ft_printf("\nPresionado Ctrl+C durante una tarea\n");
	}
	else if (signal == EOF)
	{
		if (shell_state)
			ft_printf("\nPresionado Ctrl+D en interactivo\n");
		else
			ft_printf("\nPresionado Ctrl+D durante una tarea\n");
	}
	else if (signal == SIGQUIT)
	{
		if (shell_state)
			ft_printf("\nPresionado Ctrl+\\ en interactivo\n");
		else
			ft_printf("\nPresionado Ctrl+\\ (SIGQUIT) durante una tarea\n");
	}
}

void	setup_signal_handling(struct sigaction *sa, char *input)
{
	sa->sa_handler = signal_handler;
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
}

	//term.c_lflag &= ~ECHO;
	//	sa.sa_flags = 0;
	//	sigemptyset(&sa.sa_mask);