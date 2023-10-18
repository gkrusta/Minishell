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

	while (shell->env_lst != NULL)
	{
		if (ft_strcmp(key, shell->env_lst->key) == 0)
		{
			//printf("key is %s   value is %s\n", key, shell->env_lst->value);
			value = shell->env_lst->value;
			return (value);
		}
		shell->env_lst = shell->env_lst->next;
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
	new_dir = get_value(shell, "HOME");
	if (chdir(new_dir) == -1)
	{
		printf ("minishell: cd: %s: No such file or directory\n", new_dir);
		shell->exit_status = 1;
	}
	old_dir = ft_strdup(curr_dir);
	//printf("%s   %s\n", curr_dir, new_dir);
	changes = ft_calloc(3, sizeof(char *));
	changes[0] = ft_strjoin("OLDPWD=", old_dir);
	changes[1] = ft_strjoin("PWD=", new_dir);
	if (changes[0] != NULL && changes[1] != NULL)
		export(shell, changes);
	//printf("%s   %s\n", changes[0], changes[1]);
	free_args(changes);
	free(old_dir);
}

void	cd(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	//ft_trim(shell);
	if (args[i] == NULL)
		only_cd(shell);
	if (ft_strcmp(args[i], "-") == 0)
		last_cd(shell);
}
/* 	else
	{
		if (ft_strcmp(args[i], "..") == 0)
		{
			char* current_dir = getcwd(NULL, 0);
			char* last_slash = ft_strrchr(current_dir, '/');
			if (last_slash != NULL)
				*last_slash = '\0';  // Remove the last directory in the path
			chdir(current_dir);
			//Actualizar (OLDPWD);
			//Actualizar (PWD)
			free(current_dir);
		}
		else if (ft_strcmp(args[i], "/") == 0)
			chdir("/");
	else
			check_path(shell);

			//fprintf(stderr, "cd: %s: No such directory\n", argv[1]);
*/
