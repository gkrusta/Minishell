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

void	dbg_print_command_nodes(t_cmd **com_nodes, int mode)
{
	int		i;
	t_cmd	*c_node;

	if (mode == 2)
	{
		c_node = *com_nodes;
		i = 0;
		ft_printf("\n");
		ft_printf("\033[1;38;5;226m*** debug info * command nodes ***\033[0m");
		while (com_nodes)
		{
			printf("\n      NODE %i:\n", i);
			printf("\n          cmd: %s\n", c_node->cmd);
			printf("\n         path: %s:\n", c_node->cmd_path);
			printf("\n       infile: %i:\n", c_node->infile);
			printf("\n      outfile: %i:\n", c_node->outfile);
			c_node = c_node->next;
			i++;
		}
		ft_printf("\033[1;38;5;226m**********************************\033[0m\n");
		printf("\n");
	}
}
