#include "minishell.h"

void	dbg_print_array_tokens(char **tokens, int mode)
{
	int	i;

	if (mode == 1)
	{
		i = 0;
		ft_printf("\n");
		ft_printf("\033[1;38;5;226m*** debug info * tokens array ***\033[0m\n");
		while (tokens[i])
		{
			printf("      token %i: %s\n", i, tokens[i]);
			i++;
		}
		ft_printf("\033[1;38;5;226m*********************************\033[0m\n");
		printf("\n");
	}
}
