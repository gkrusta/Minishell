#include "minishell.h"

void	add_argument(t_shell *shell, char *token, t_cmd *node)
{
	int	i;

	if (!node->cmd[0])
	{
		if (is_in_path(shell, token) || is_built_in(token))
		{
			node->cmd = str_change_value(node->cmd, token);
			if (!is_built_in(token))
				node->cmd_path = find_path(token, shell->env, node->cmd_path);
		}
		else
		{
			i = 0;
			while (node->args[i])
				i++;
			node->args[i] = str_change_value(node->args[i], token);
		}
	}
	else
	{
		i = 0;
		while (node->args[i])
			i++;
		node->args[i] = str_change_value(node->args[i], token);
	}
}

int	is_argument(char *token)
{
	int	type;

	type = assign_type(token[0]);
	if (type == 0 || type == 4)
		return (1);
	else
		return (0);
}

void	make_nodes(t_shell *shell, char *input, int mode)
{
	int		i;
	t_cmd	**exec_nodes;
	t_cmd	*new_node;
	int		fd_in;

	i = 0;
	fd_in = 0;
	new_node = NULL;
	exec_nodes = ft_calloc(1, sizeof(t_cmd *));
	while (shell->tokens[i])
	{
		if (!new_node || (new_node && new_node->cmd[0]))
		{
			new_node = lst_new_node();
			ft_add_back_node(exec_nodes, new_node);
		}
		while (shell->tokens[i] && is_argument(shell->tokens[i]))
		{
			add_argument(shell, shell->tokens[i], new_node);
			if (!shell->tokens[i + 1])
				check_redir(new_node, shell->tokens, &i, &fd_in);
			i++;
		}
		if (shell->tokens[i])
		{
			check_redir(new_node, shell->tokens, &i, &fd_in);
			i++;
		}
	}
	dbg_print_command_nodes(exec_nodes, mode);
	execute_nodes(exec_nodes, shell);
	lst_clear_nodes(exec_nodes);
	free(input);
	free_tokens(shell);
}
