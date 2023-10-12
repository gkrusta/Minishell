#include "minishell.h"

void	free_arg(char *arg_key, char *arg_value)
{
	if (arg_key)
		free(arg_key);
	if (arg_value)
		free(arg_value);
}

