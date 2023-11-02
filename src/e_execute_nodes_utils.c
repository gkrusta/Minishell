#include "minishell.h"

int	check_absolut(t_cmd *node)
{
	char	*str;
	int		i;

	i = 0;
	if (node->cmd[0] == '\0' && node->args[0][0] == '/')
	{
		str = ft_strrchr(node->args[0], '/');
		free(node->cmd);
		node->cmd = ft_strdup(&str[1]);
		free(node->cmd_path);
		node->cmd_path = ft_strdup(node->args[0]);
		while (i < 9)
		{
			node->args[i] = node->args[i + 1];
			i++;
		}
		return (1);
	}
	return (0);
}
