#include "minishell.h"

void	print_header(void)
{
	system("clear");
	ft_printf("\n");
	ft_printf("****************************************************\n");
	ft_printf("*     42 PROJECT                                   *\n");
	ft_printf("*    - MINISHELL -   version: 0.0.1                *\n");
	ft_printf("*                                                  *\n");
	ft_printf("*    By: gkrusta <gkrusta@student.42malaga.com>    *\n");
	ft_printf("*        pvilchez <pvilchez@student.42.fr>         *\n");
	ft_printf("****************************************************\n\n");
}

void	mini_args(int argc, char *argv[], int *mode)
{
	int	i;

	i = 0;
	*mode = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-h") == 0)
			print_header();
		if (ft_strcmp(argv[i], "-d") == 0)
			*mode = 1;
		i++;
	}
}
