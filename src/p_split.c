#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v')
		return (1);
	if (c == '\f' || c == '\r' || c == ' ' || c == '\0')
		return (1);
	return (0);
}

char	**add_token(char **splited, char *buff)
{
	char	**aux;
	int		i;

	i = 0;
	while (splited[i])
		i++;
	aux = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (splited[i])
	{
		aux[i] = splited[i];
		i++;
	}
	aux[i] = buff;
	//free(splited);
	return (aux);
}

int	chk_end_token(char *input, int *i, int *start)
{
	static int	type;

	if (*start == 0)
	{
		*start = 1;
		type = assign_type(input[*i]);
	}
	if (continue_read(input[*i], type, *start))
		return (1);
	return (0);
}

char	*read_token(char *input, int *i)
{
	char	*c;
	char	*aux;
	char	*buff;
	int		start;

	c = ft_calloc(sizeof(char), 2);
	buff = ft_calloc(sizeof(char), 1);
	start = 0;
	while (!ft_isspace(input[*i]) && chk_end_token(input, i, &start))
	{
		c[0] = input[*i];
		aux = buff;
		buff = ft_strjoin(aux, c);
		//free(c);
		//free(aux);
		*i = *i + 1;
	}
	return (buff);
}

char	**p_split(char *input)
{
	int		i;
	char	**tokens;
	char	*buff;

	i = 0;
	tokens = ft_calloc(sizeof(char *), 1);
	while (input[i])
	{
		if (!ft_isspace(input[i]))
		{
			buff = read_token(input, &i);
			tokens = add_token(tokens, buff);
			//free(buff);
		}
		else
			i++;
	}
	i = 0;
	while (tokens[i])
	{
		ft_printf("%s\n", tokens[i]);
		i++;
	}
	return (tokens);
}
