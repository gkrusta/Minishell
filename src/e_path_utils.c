#include "minishell.h"

void	free_path(char **str_list, char *empty_str)
{
	int		i;

	i = 0;
	while (str_list[i])
	{
		free(str_list[i]);
		i++;
	}
	if (empty_str)
		free(empty_str);
	free(str_list);
}

char	*find_path(char *command, char **envp, char *empty_str)
{
	char	**path_list;
	char	*path_root;
	char	*final_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	path_list = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_list[i])
	{
		path_root = ft_strjoin(path_list[i], "/");
		final_path = ft_strjoin(path_root, command);
		free(path_root);
		if (access(final_path, F_OK) == 0)
		{
			free_path(path_list, empty_str);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	free_path(path_list, empty_str);
	return (0);
}

int	is_in_path(t_shell *shell, char *str)
{
	char	*aux;
	char	*empty_str;

	empty_str = NULL;
	aux = find_path(str, shell->env, empty_str);
	if (aux)
	{
		free(aux);
		return (1);
	}
	else
		return (0);
}
