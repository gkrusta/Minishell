#include "minishell.h"

void	free_node(t_list *node)
{
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	delete_value(t_shell *shell, int node_pos)
{
	t_list	*node;
	t_list	*aux;
	int		i;

	node = shell->env_lst;
	if (node_pos == 0)
	{
		aux = node;
		shell->env_lst = shell->env_lst->next;
		free_node(aux);
	}
	else
	{
		i = 0;
		while (i < node_pos)
		{
			aux = node;
			node = node->next;
			i++;
		}
		aux->next = node->next;
		free_node(node);
	}
}

void	unset(t_shell *shell, char **args)
{
	t_list	*env_list;
	int		i;
	int		found;
	t_list	*new_arg;
	int		node_pos;

	i = 0;
	while (args[i])
	{
		found = 0;
		node_pos = 0;
		new_arg = ft_calloc(1, sizeof(t_list));
		env_list = shell->env_lst;
		extract_values(args[i], new_arg);
		while (env_list && found == 0 && check_key(new_arg->key, 1))
		{
			if (key_found(new_arg->key, (char *)env_list->key, &found))
				delete_value(shell, node_pos);
			env_list = env_list->next;
			node_pos++;
		}
		free_arg(new_arg);
		i++;
	}
}
