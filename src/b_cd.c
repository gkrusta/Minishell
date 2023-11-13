#include "minishell.h"

void	abs_path(t_shell *shell, char *path)
{
	char	*tmp;
	char	*new_dir;
	char	*old_dir;

	old_dir = getcwd(shell->path, 128);
	if (old_dir == NULL)
	{
		ft_printf("minishell: cd: %s not set\n", shell->env_lst->key);
		shell->exit_status = 1;
		//exit(1);
	}
	else
	{
		if (ft_strcmp(old_dir, "/") == 0)
			tmp = ft_strdup("/");
		else
			tmp = ft_strjoin(old_dir, "/");
		new_dir = ft_strjoin(tmp, path);
		free(tmp);
		ft_export_pwds(shell, old_dir, new_dir);
		free(new_dir);
	}
}

void	home_cd(t_shell *shell, char *path)
{
	char	*new_dir;
	char	*old_dir;

	old_dir = getcwd(shell->path, 128);
	if (old_dir == NULL)
	{
		ft_printf("minishell: cd: %s not set\n", shell->env_lst->key);
		shell->exit_status = 1;
		//exit(1);
	}
	else
	{
		if (ft_strcmp(path, "/") == 0)
			new_dir = ft_strdup("/");
		else
			new_dir = get_value(shell, path);
		if (new_dir != NULL)
		{
			ft_export_pwds(shell, old_dir, new_dir);
			if (ft_strcmp(path, "OLDPWD") == 0)
				ft_printf("%s\n", get_value(shell, "PWD"));
			else if (ft_strcmp(path, "/") == 0)
				free (new_dir);
		}
	}
}

void	parent_dir(t_shell *shell)
{
	char	*new_dir;
	char	*old_dir;
	char	*last_slash;

	old_dir = getcwd(shell->path, 128);
	if (old_dir == NULL)
	{
		ft_printf("minishell: cd: %s not set\n", shell->env_lst->key);
		shell->exit_status = 1;
		//exit(1);
	}
	else
	{
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
}

void	cd_type(t_shell *shell, char **dir, int i)
{
	if (ft_strcmp(dir[i], "-") == 0)
		home_cd(shell, "OLDPWD");
	else if (ft_strcmp(dir[i], "~") == 0)
		home_cd(shell, "HOME");
	else if (ft_strcmp(dir[i], "..") == 0)
		parent_dir(shell);
	else
		abs_path(shell, dir[i]);
}

void	cd(t_shell *shell, char **args)
{
	int		i;
	char	**dir;

	i = 0;
	if (args[i] == NULL)
		home_cd(shell, "HOME");
	else if (ft_strcmp(args[i], "/") == 0) 
		home_cd(shell, "/");
	else
	{
		dir = ft_split(args[i], '/');
		if (ft_strcmp(dir[i], ".") == 0)
			i++;
		while (dir[i])
		{
			cd_type(shell, dir, i);
			i++;
		}
		free_args(dir);
	}
}
