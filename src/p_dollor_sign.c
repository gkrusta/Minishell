#include "minishell.h"

void	varible_search(t_shell **env_copy, char *var)
{
	char	*envp_path;
	int		i;

	i = 0;
	envp_path = 0;
	while (env_copy[i])
	{
		if (ft_strncmp(env_copy[i], var, ft_strlen(var)) == 0)
		{
			
			break ;
		}
		i++;
	}
/* 	if (!envp_path)
		error("Error: "); */
	//p->path = ft_split(envp_path, ':');
}

// to detect "$" character in a token
char	*ft_token_check(char **tokens)
{
	int		i;
	char	*var;

	i = 0;
	while (tokens[i])
	{
		if (ft_strchr(token, '$') != NULL)
		{
			// Token contains "$" character, proceed to extract the variable name
		}

	}
	return (var);
}
