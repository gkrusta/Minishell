#include "minishell.h"

char	*find_path(char *command, char **envp)
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
			free_str_list(path_list);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	free_str_list(path_list);
	return (0);
}
