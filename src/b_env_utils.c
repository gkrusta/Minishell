/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:35:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/26 13:39:23 by gkrusta          ###   ########.fr       */
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
