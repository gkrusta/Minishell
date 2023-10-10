#include "minishell.h"

int	is_special_char(char c)
{
	if(c == '0')
		return (1);
	return (0);
}

char	*add_spaces(char *str)
{
	int		i;
	char	*res;
	char	*aux;

	i = 0;
	res = ft_calloc(sizeof(char), 1);
	while (str[i])
	{
		if (is_special(str[i]))
		{
			aux = res;
			res = ft_strjoin(res, ' ');
			free(aux);
		}
		aux = res;
		res = ft_strjoin(res, str[i]);
		free(aux);
	}
	free(str);
	ft_printf("Before: %s\n After: %s", str, res);
	return (res);
}
