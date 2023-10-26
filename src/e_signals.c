#include "minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (shell_state)
			printf("\nSe ha presionado Ctrl+C en interactivo\n");
		else
			printf("\nSe ha presionado Ctrl+C durante una tarea\n");
	}
	else if (signal == EOF)
	{
		if (shell_state)
			printf("\nSe ha presionado Ctrl+D en interactivo\n");
		else
			printf("\nSe ha presionado Ctrl+D durante una tarea\n");
	}
	else if (signal == SIGQUIT)
	{
		if (shell_state)
			printf("\nSe ha presionado Ctrl+\\ en interactivo\n");
		else
			printf("\nSe ha presionado Ctrl+\\ (SIGQUIT) durante una tarea\n");
	}
}

void	setup_signal_handling(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
