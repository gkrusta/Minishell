/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/11 13:30:27 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void ft_leaks(void)
{
	system("leaks -q minishell");
} */

/* char	*ft_strndup(const char *str, size_t len)
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
	s[i] = '\0';
	return (s);
} */

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

void	free_params(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env_copy[i] != NULL)
		free(shell->env_copy[i++]);
	free(shell->env_copy);
	free(shell);
}

char	*ft_strcpy(char *src, int size)
{
	int		i;
	char	*dest = NULL;

	if (size > 0)
	{
		i = 0;
		while (src[i] && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (dest);
}

void	create_env_lst(t_shell *shell, char **envp)
{
	t_list	*env;
	char	*key;
	char	*value;
	int		i;
	char	*limiter;

	i = 0;
	while (envp[i])
	{
		limiter = ft_strchr(envp[i], '=');
		key = ft_strcpy(*envp, *envp - limiter);
		printf("key is %s and limit shit  is %s and lenght is %ld\n", key, limiter, limiter - envp[i]);
		value = ft_strcpy(limiter, 100);
		env = ft_lstnew(key, value);
		ft_lstadd_back(&(shell->env_lst_copy), env);
		//free(key);
		//free(value);
		i++;
	}
}

void	parse_env(t_shell *shell, char **envp)
{
	shell->env_copy = ft_strddup((const char **)envp);
/* 	for (int i = 0; shell->env_copy[i] != NULL; i++) // to print
	{
		printf("Copied: %s\n", shell->env_copy[i]);
	} */
	//shell->env_lst_copy = create_env_lst(shell, envp);
	create_env_lst(shell, envp);
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*username;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	//atexit(ft_leaks);
	username = getenv("USER");
	printf("\n\nUSER is: @%s\n", username); 
	while (1)
	{
		input = readline("minishell> ");
		if (!input) // si usario hace un click a ctrl + d significa que readline ha devuelto NULL
		{
			printf("\n");
			break ; // exit shell
		}
		parse_env(shell, envp);
/* 		if (strcmp(input, "env") == 0) // imprime el path
		{
			i = 0;
			while (envp[i])
			{
				printf("%s\n", envp[i]);
				i++;
			}	
		} */
		if (ft_strlen(input) > 0)
			add_history(input);
		printf("added to history: %s\n", input);
		free(input);
		free_params(shell);
	}
	return (0);
}