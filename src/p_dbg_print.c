#include "minishell.h"

void	dbg_print_array_tokens(char **tokens, int mode, t_shell *shell)
{
	int	i;

	if (mode == 1 || mode == 3)
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
		printf("Space next: %s\n", shell->space_next);
		printf("\n");
	}
}

void	dbg_print_command_nodes(t_cmd **com_nodes, int mode)
{
	int		i;
	int		j;
	t_cmd	*c_node;

	if (mode == 2 || mode == 3)
	{
		c_node = *com_nodes;
		i = 1;
		ft_printf("\n");
		ft_printf("\033[1;38;5;226m** debug info * command nodes **\033[0m");
		while (c_node)
		{
			printf("\n       NODE %i\n        cmd: %s\n", i, c_node->cmd);
			printf("       path: %s\n       args: ", c_node->cmd_path);
			j = 0;
			while (c_node->args[j])
				printf("%s  ", c_node->args[j++]);
			printf("\n     infile: %i\n", c_node->infile);
			printf("    outfile: %i\n", c_node->outfile);
			c_node = c_node->next;
			i++;
		}
		ft_printf("\033[1;38;5;226m********************************\033[0m\n");
		printf("\n");
	}
}
