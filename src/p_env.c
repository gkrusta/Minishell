/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvilchez <pvilchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:55:15 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/12 15:25:10 by pvilchez         ###   ########.fr       */
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
	char	**env_copy;

	i = 0;
	if (envp == NULL)
		return (NULL);
	while(envp[i] != NULL)
		i++;
	env_copy = malloc(sizeof(char *) * (i + 1));
	if (!env_copy)
		return (0);
	i = 0;
	while (envp[i])
	{
		env_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
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
			ft_lstadd_back(&(shell->env_lst_copy), env);
			free(key);
			free(value);
		}
		i++;
	}
}

void	print_env_variables(t_list *env)
{
	t_list	*env_print;

	env_print = env;
	while (env_print != NULL)
	{
		printf("%s=%s\n", env_print->key, env_print->value);
		env_print = env_print->next;
	}
}

void	free_params(t_shell *shell)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (shell->env_copy[i] != NULL)
		free(shell->env_copy[i++]);
	free(shell->env_copy);
	while (shell->env_lst_copy)
	{
		tmp = shell->env_lst_copy;
		shell->env_lst_copy = shell->env_lst_copy->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free(shell);
}
