#include "minishell.h"

int	is_argument(t_shell *shell, char *token)
{
	if (is_build(token))
		return (2);
	else if (is_in_path(shell, token))
		return (2);
	else
	return (0);
}

void	execute_input(t_shell *shell, char *input, int mode)
{
	int		i;
	t_cmd	**exec_nodes;

	add_history(input);
	shell->tokens = p_split(input);
	dbg_print_array_tokens(shell->tokens, mode);
	//ft_trim(shell);
	while (shell->tokens[i])
	{
		if (is_argument(shell, shell->tokens[i]) == 2)
			// TODO crear nuevo nodo
		if (is_argument(shell, shell->tokens[i]) > 0)
			add_arg_to_node(shell->tokens[i]);
		i++;
	}
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
	free(input);
	free_tokens(shell);
}
