/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:30:52 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/10 16:43:34 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void ft_leaks(void)
{
	system("leaks -q minishell");
} */

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
	s[i] = '\0';
	return (s);
}

void	parse_env(t_shell *shell, char **envp)
{
	t_list	*env;
	char	*key;
	char	*value;
	int		i;
	char	*limiter;

	i = 0;
	while (*envp)
	{
		limiter = ft_strchr(*envp, '=');
		key = ft_strndup(*envp, limiter - *envp);
		printf("key is %s and %ld\n", key, limiter - *envp);
		value = ft_strdup(limiter + 1);
		env = ft_lstnew(key, value);
		ft_lstadd_back(&(shell->path), env);
		free(key);
		free(value);
		envp++;
	}

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
		parse_env(shell, envp); // here
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
	}
	return (0);
}