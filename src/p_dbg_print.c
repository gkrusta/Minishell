#include "minishell.h"

void	dbg_print_array_tokens(char **tokens)
{
	int	i;

	i = 0;
	printf("\n");
	while (tokens[i])
	{
		printf("token %i: %s\n", i, tokens[i]);
		i++;
	}
	printf("\n");
}
