#include "minishell.h"

void replaceTokenWithValue(char **token, const char *var)
{
	// Calculate the new length of the token
	size_t tokenLength = ft_strlen(*token);
	size_t newValueLength = ft_strlen(var);
	size_t newTokenLength = tokenLength - 2 + newValueLength; // Subtract 2 for "$" and variable name

	// Allocate memory for the new token
	char *newToken = (char *)malloc(newTokenLength + 1); // +1 for the null terminator

	// Copy the part of the original token before "$variable"
	strncpy(newToken, *token, token - *token);

	// Copy the variable value
	strcpy(newToken + (token - *token), var);

	// Copy the part of the original token after "$variable"
	strcpy(newToken + (token - *token) + newValueLength, *token + (token - *token) + 2);

	// Update the token pointer
	*token = newToken;
}


char	*varible_search(char **env, char *var)
{
	char	*var_new;
	int		i;
	int		j;
	size_t	var_new_len;

	i = 0;
	j = 0;
	while (env[i])
	{
		while (env[i][j])
		{
			if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			{
				j++;
				if (ft_strchr(env[i][j], '=') == 0)
				{
					var_new_len = ft_strlen(env[i]) - ft_strlen(var) - 1;
					var_new = malloc(sizeof(char) * var_new_len);
					while (i < var_new_len)
					{
						var_new[i] = env[i][j];
						i++;
						j++;
					}
				}
			}
			else
				break ;
		}
		i++;
	}
	return NULL;
}



int	check_end(char *str, int pos)
{
	pos++;
	while (str[pos])
	{
		if (str[pos] == 34)
			return (0);
		pos++;
	}
	return (1);
}

char	*after_dolor_sign(t_shell *shell, char *str)
{
	int		i;
	int		count;
	char	*var;
	
	i = 1;
	count = 0;
	while (str[i])
	{
		if (!(str[i] > 47 && str[i] < 58) || !(str[i] > 64 && str[i] < 91)
			|| !(str[i] > 96 && str[i] < 123) || !str[i] == 95)
				break ;
		i++;
	}
	var = malloc(sizeof(char) * i);
	count = i;
	i = 0;
	while (i < count)
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	if (varible_search(shell, var) == 0)
		return (var);
	else
		return NULL;
}

// to detect "$" character in a token
void	ft_token_check(t_shell *shell)
{
	int			i;
	int			j;
	const char	*var;

	i = 0;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			if (tokens[i][j] == 34 && tokens[i][j + 1] != 34 && check_end(tokens[i], j) != 1)
			{
				j++
				if (ft_strchr(token[i], '$') != NULL)
				{
					var = after_dolor_sign(shell, tokens[i])
					if (var)
						replaceTokenWithValue(tokens, var);
					else
						write (1, "\n", 1);
				}
				//write (1, tokens[i][j], 1);
			}
			j++;
		}
		i++;
	}
}
