#include "minishell.h"

// if pair "" or ' is found return the lenght of content
int	pair_exists(char *str, char c)
{
	int	len;
	int	i;

	len = 0;
	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			return (len);
		i++;
		len++;
	}
	printf("Error");// pair not found
	exit(1);
}

char *trim_quotes(char *str)
{
	char	*result;
	int		len;

	if (str == NULL)
		return NULL;
	result = NULL;
	if (str[2] != '\0' && str[0] == 34)
	{
		len = pair_exists(str, 34);
		if (len > 0)
			result = ft_substr(str, 1, len);
	}
	else if (str[2] != '\0' && str[0] == 39)
	{
		len = pair_exists(str, 39);
		if (len > 0)
			result = ft_substr(str, 1, len);
		printf("len s %d    result is %s\n", len, result);
	}
	else
		result = ft_strdup("");
	printf(" result is %s\n", result);
	free (str);
	return (result);
}

// Function to trim extra double quotes (") and single quotes (') from a string
int	ft_trim(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->tokens[i])
	{
		if (shell->tokens[i][0] == 34)
			ft_token_check(shell->tokens[i]);
		else if (shell->tokens[i][0] == 39)
			shell->tokens[i] = trim_quotes(shell->tokens[i]);
		i++;
	}
	return (0);
}
