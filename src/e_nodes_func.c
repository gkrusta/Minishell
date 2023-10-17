#include "minishell.h"

void	ft_lstclear_nodes(t_cmd **lst)
{
	t_cmd	*node;
	t_cmd	*aux;

	node = *lst;
	while (node != NULL)
	{
		aux = node;
		node = node->next;
		free(aux->cmd);
		free(aux->cmd_path);
		free(aux);
	}
	*lst = node;
}

t_cmd	*ft_lstnew_node(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	node->cmd = ft_calloc(1, sizeof(char));
	node->cmd_path = ft_calloc(1, sizeof(char));
	node->infile = 0;
	node->outfile = 1;
	node->next = NULL;
	return (node);
}
