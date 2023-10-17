#include "minishell.h"

void	add_argument(t_shell *shell, char *token, t_cmd *node)
{
	int	i;

	if (!node->cmd)
	{
		node->cmd = token;
		if (!is_built_in)
			node->cmd_path = find_path(token, shell->env_lst);
	}
	else
	{
		i = 0;
		while (node->args[i])
			i++;
		node->args[i] = token;
	}
}

int	is_argument(t_shell *shell, char *token)
{
	int	type;

	type = assign_type(token[0]);
	if (type == 0 || type == 3 || type == 4)
		return (1);
	else
		return (0);
}

void	make_nodes(t_shell *shell, char *input, int mode)
{
	int		i;
	t_cmd	**exec_nodes;
	t_cmd	*new_node;

	while (shell->tokens[i])
	{
		new_node = lst_new_node;
		ft_lstadd_back(exec_nodes, new_node);
		while (shell->tokens[i] && is_argument(shell, shell->tokens[i]))
		{
			add_argument(shell, shell->tokens[i], new_node);
			i++;
		}
		if (shell->tokens[i])
		{
			//check_redir(shell->tokens[i]);
			i++;
		}
	}
	//TODO execute_nodes
	dbg_print_command_nodes(exec_nodes, mode);
	free(input);
	free_tokens(shell);
}

/*

	if (strcmp(shell->tokens[0], "env") == 0)
	{
		if (!shell->tokens[1])
			print_env_variables(shell->env_lst);
		else
		{
			printf("Error. env no recibe parámetros\n");
			shell->exit_status = 127;
		}
	}
	if (strcmp(shell->tokens[0], "export") == 0)
		export(shell, &shell->tokens[1]);
	if (strcmp(shell->tokens[0], "unset") == 0)
		unset(shell, &shell->tokens[1]);




*/