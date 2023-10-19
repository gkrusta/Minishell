#include "minishell.h"

void	abs_path(t_shell *shell, char *path)
{
	char	*tmp;
	char	*new_dir;
	char	*old_dir;

	old_dir = getcwd(shell->path, 128);
	if (old_dir == NULL)
	{
		printf("minishell: cd: %s: not set\n", shell->env_lst->key);
		shell->exit_status = 1;
		//exit(1);
	}
	tmp = ft_strjoin(old_dir, "/");
	new_dir = ft_strjoin(tmp, path);
	free(tmp);
	ft_export_pwds(shell, old_dir, new_dir);
	free(new_dir);
}

void	last_cd(t_shell *shell)
{
	char	*new_dir;
	char	*old_dir;

	old_dir = getcwd(shell->path, 128);
	if (old_dir == NULL)
	{
		printf("minishell: cd: %s: not set\n", shell->env_lst->key);
		shell->exit_status = 1;
		//exit(1);
	}
	new_dir = get_value(shell, "OLDPWD");
	ft_export_pwds(shell, old_dir, new_dir);
}

void	only_cd(t_shell *shell)
{
	char	*new_dir;
	char	*old_dir;

	old_dir = getcwd(shell->path, 128);
	if (old_dir == NULL)
	{
		printf("minishell: cd: %s: not set\n", shell->env_lst->key);
		shell->exit_status = 1;
		//exit(1);
	}
	new_dir = get_value(shell, "HOME");
	ft_export_pwds(shell, old_dir, new_dir);
	//free(old_dir);*/
}

void	root_cd(t_shell *shell)
{
	char	*new_dir;
	char	*old_dir;

	old_dir = getcwd(shell->path, 128);
	if (old_dir == NULL)
	{
		printf("minishell: cd: %s: not set\n", shell->env_lst->key);
		shell->exit_status = 1;
		//exit(1);
	}
	new_dir = ft_strdup("/");
	ft_export_pwds(shell, old_dir, new_dir);
	free(new_dir);
}

void	parent_dir(t_shell *shell)
{
	char	*new_dir;
	char	*old_dir;
	char	*last_slash;

	old_dir = getcwd(shell->path, 128);
	if (old_dir == NULL)
	{
		printf("minishell: cd: %s: not set\n", shell->env_lst->key);
		shell->exit_status = 1;
		//exit(1);
	}
	new_dir = ft_strdup(old_dir);
	last_slash = ft_strrchr(new_dir, '/');
	if (last_slash != NULL && new_dir != last_slash)
		*last_slash = '\0';
	else if (last_slash != NULL && new_dir == last_slash)
	{
		free(new_dir);
		new_dir = ft_strdup("/");
	}
	ft_export_pwds(shell, old_dir, new_dir);
	free (new_dir);
}

void	cd(t_shell *shell, char **args)
{
	int		i;
	char	**dir;

	i = 0;
	//ft_trim(shell);
	if (args[i] == NULL)
		only_cd(shell);
	else
	{
		dir = ft_split(args[i], '/');
		if (ft_strcmp(dir[i], ".") == 0)
			i++;
		while (dir[i])
		{
			if (ft_strcmp(dir[i], "-") == 0)
				last_cd(shell);
			else if (ft_strcmp(dir[i], "/") == 0) // seg fault
				root_cd(shell);
			else if (ft_strcmp(dir[i], "..") == 0)
				parent_dir(shell);
			else
				abs_path(shell, dir[i]);
			i++;
		}
		free_args(dir);
		//fprintf(stderr, "cd: %s: No such directory\n", argv[1]);
	}
}