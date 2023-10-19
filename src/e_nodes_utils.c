#include "minishell.h"

void	ft_add_front_node(t_cmd **lst, t_cmd *new_node)
{
	if (lst && new_node)
	{
		new_node->next = *lst;
		*lst = new_node;
	}
}

void	ft_add_back_node(t_cmd **lst, t_cmd *new_node)
{
	t_cmd	*tmp;

	if (*lst == NULL)
		*lst = new_node;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
		new_node->next = NULL;
	}
}

void	lst_clear_nodes(t_cmd **lst)
{
	t_cmd	*node;
	t_cmd	*aux;
	int		i;

	node = *lst;
	while (node != NULL)
	{
		aux = node;
		node = node->next;
		free(aux->cmd_path);
		i = 0;
		while (aux->args[i++])
			free(aux->args[i]);
		free(aux->args);
		free(aux);
	}
	*lst = node;
}

t_cmd	*lst_new_node(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	node->cmd = NULL;
	node->cmd_path = ft_calloc(1, sizeof(char));
	node->args = ft_calloc(10, sizeof(char *));
	node->infile = 0;
	node->outfile = 1;
	node->next = NULL;
	return (node);
}
