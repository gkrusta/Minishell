#include "minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	*get_value(t_shell *shell, char *key)
{
	char	*value;
	t_list	*env_list;

	env_list = shell->env_lst;
	while (env_list != NULL)
	{
		if (ft_strcmp(key, env_list->key) == 0)
		{
			value = env_list->value;
			return (value);
		}
		env_list = env_list->next;
	}
	printf("minishell: cd: %s not set\n", key);
	shell->exit_status = 1;
	return (NULL);
}

void	ft_export_pwds(t_shell *shell, char *old_dir, char *new_dir)
{
	char	**changes;
	char	*dir;

	dir = ft_strrchr(new_dir, '/');
	if (chdir(new_dir) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", &dir[1]);
		shell->exit_status = 1;
	}
	changes = ft_calloc(3, sizeof(char *));
	changes[0] = ft_strjoin("OLDPWD=", old_dir);
	changes[1] = ft_strjoin("PWD=", new_dir);
	if (changes[0] != NULL && changes[1] != NULL)
		export(shell, changes);
	free_args(changes);
}