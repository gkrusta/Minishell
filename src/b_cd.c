#include "minishell.h"

/* void	check_path(t_shell *shell)
{
	ft_trim(shell);
	if (access(shell->tokens[1], F_OK) == 0)
	chdir
	if (chdir(shell->tokens[1]) != 0)
		perror("cd");
} */

void	last_cd(t_shell *shell)
{
	char	*curr_dir;
	char	*new_dir;
	char	*old_dir;
	char	**changes;

	curr_dir = getcwd(shell->path, 128);
	if (curr_dir == NULL)
	{
		printf("minishell: cd: %s: not set\n", shell->env_lst->key);
		shell->exit_status = 1;
		//exit(1);
	}
	new_dir = get_value(shell, "OLDPWD");
	if (chdir(new_dir) == -1)
	{
		printf("minishell: cd: %s: not set\n", new_dir);
		shell->exit_status = 1;
	}
	old_dir = ft_strdup(curr_dir);
	//free(curr_dir);
	changes = ft_calloc(3, sizeof(char *));
	changes[0] = ft_strjoin("OLDPWD=", old_dir);
	changes[1] = ft_strjoin("PWD=", new_dir);
	if (changes[0] != NULL && changes[1] != NULL)
		export(shell, changes);
	free_args(changes);
	printf("%s\n", old_dir);
	free(old_dir);
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
			//printf("key is %s   value is %s\n", key, shell->env_lst->value);
			value = env_list->value;
			return (value);
		}
		env_list = env_list->next;
	}
	printf("minishell: cd: %s: not set\n", key);
	shell->exit_status = 1;
	return (NULL);
}

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

void	only_cd(t_shell *shell)
{
	char	*new_dir;
	char	*old_dir;
	char	**changes;

	old_dir = getcwd(shell->path, 128);
	if (old_dir == NULL)
	{
		printf("minishell: cd: %s: not set\n", shell->env_lst->key);
		shell->exit_status = 1;
		//exit(1);
	}
	new_dir = get_value(shell, "HOME");
	if (chdir(new_dir) == -1)
	{
		printf ("minishell: cd: %s: No such file or directory\n", new_dir);
		shell->exit_status = 1;
	}
	printf("%s   %s\n", old_dir, new_dir);
	changes = ft_calloc(3, sizeof(char *));
	changes[0] = ft_strjoin("OLDPWD=", old_dir);
	changes[1] = ft_strjoin("PWD=", new_dir);
	changes[2] = NULL;
	if (changes[0] != NULL && changes[1] != NULL)
		export(shell, changes);
	printf("%s   %s\n", changes[0], changes[1]);
	free_args(changes);
	//free(old_dir);*/
}

void	root_cd(t_shell *shell)
{
	char	*new_dir;
	char	*old_dir;
	char	**changes;

	old_dir = getcwd(shell->path, 128);
	if (old_dir == NULL)
	{
		printf("minishell: cd: %s: not set\n", shell->env_lst->key);
		shell->exit_status = 1;
		//exit(1);
	}
	new_dir = ft_strdup("/");
	if (chdir("/") == -1)
	{
		printf("minishell: cd: %s: not set\n", new_dir);
		shell->exit_status = 1;
	}
	changes = ft_calloc(3, sizeof(char *));
	changes[0] = ft_strjoin("OLDPWD=", old_dir);
	changes[1] = ft_strjoin("PWD=", new_dir);
	if (changes[0] != NULL && changes[1] != NULL)
		export(shell, changes);
	free_args(changes);
	free(new_dir);
}

void	parent_dir(t_shell *shell)
{
	char	*new_dir;
	char	*old_dir;
	char	**changes;

	old_dir = getcwd(shell->path, 128);
	if (old_dir == NULL)
	{
		printf("minishell: cd: %s: not set\n", shell->env_lst->key);
		shell->exit_status = 1;
		//exit(1);
	}
	new_dir = ft_strdup("/");
	if (chdir("/") == -1)
	{
		printf("minishell: cd: %s: not set\n", new_dir);
		shell->exit_status = 1;
	}
	changes = ft_calloc(3, sizeof(char *));
	changes[0] = ft_strjoin("OLDPWD=", old_dir);
	changes[1] = ft_strjoin("PWD=", new_dir);
	changes[2] = NULL;
	if (changes[0] != NULL && changes[1] != NULL)
		export(shell, changes);
	free_args(changes);
	free(new_dir);
}

void	cd(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	//ft_trim(shell);
	if (args[i] == NULL)
		only_cd(shell);
	else if (ft_strcmp(args[i], "-") == 0)
		last_cd(shell);
	else if (ft_strcmp(args[i], "/") == 0)
		root_cd(shell);
	else if (ft_strcmp(args[i], "..") == 0)
		parent_dir(shell);
	printf("HERE!@#$\n");
	//fprintf(stderr, "cd: %s: No such directory\n", argv[1]);
}