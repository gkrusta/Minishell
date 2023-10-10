#include "minishell.h"

int	assign_type(char c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (2);
	else if (c == '|')
		return (3);
	else if (c == '"')
		return (4);
	else if (c == 39)
		return (5);
	else if (ft_isspace(c))
		return (6);
	else
		return (0);
}

int	end_token(char c, int type, int start, int *used)
{
	int	new_type;

	new_type = assign_type(c);
	if (type == new_type)
	{
		if (type == 1 && c == '<')
			*used = *used + 1;
		else if (type == 2 && c == '>')
			*used = *used + 1;
		else if (type == 3 && c == '|')
			*used = *used + 1;
		else if (type == 4 && c == '"')
			*used = *used + 1;
		else if (type == 5 && c == 39)
			*used = *used + 1;
		if (type >= 1 && type <= 5 && *used >= 2)
			return (1);
		return (0);
	}
	return (1);
}
