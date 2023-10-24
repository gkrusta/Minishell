/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:55:15 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/24 16:11:29 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *str, size_t len)
{
	size_t	i;
	char	*s;

	i = 0;
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (0);
	while (i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[len] = '\0';
	return (s);
}

char	**ft_strddup(const char **envp)
{
	int		i;
	char	**env;

	i = 0;
	if (envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (0);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	create_env_lst(t_shell *shell, char **envp)
{
	t_list	*env;
	char	*key;
	char	*value;
	int		i;
	char	*limiter;

	i = 0;
	while (envp[i] != NULL)
	{
		limiter = ft_strchr(envp[i], '=');
		if (limiter)
		{
			key = ft_strndup((const char *)envp[i], limiter - envp[i]);
			value = ft_strdup(limiter + 1);
			env = ft_lstnew(key, value);
			env->init = 1;
			ft_lstadd_back(&(shell->env_lst), env);
			free(key);
			free(value);
		}
		i++;
	}
}

int	key_path_found(t_list *env)
{
	t_list	*env_key_search;
	
	env_key_search = env;
	while (env_key_search)
	{
		if (ft_strcmp(env_key_search->key, "PATH") == 0)
			return (0);
		env_key_search = env_key_search->next;
	}
	return (1);
}

void	print_env_variables(t_shell *shell, t_list *env)
{
	t_list	*env_print;

	env_print = env;
	if (env_print == NULL || key_path_found(env) == 1)
	{
		printf("Minishell: env: No such file or directory\n");
		shell->exit_status = 127;
	}
	while (env_print != NULL && env_print->init > 0)
	{
		printf("%s=%s\n", (char *)env_print->key, (char *)env_print->value);
		env_print = env_print->next;
	}
}

void	free_params(t_shell *shell)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (shell->env[i] != NULL)
		free(shell->env[i++]);
	free(shell->env);
	while (shell->env_lst)
	{
		tmp = shell->env_lst;
		shell->env_lst = shell->env_lst->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free(shell);
}
