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
	else
		return (0);
}

int	continue_read(char c, int type, int start)
{
	static int	used;

	if (start == 0)
		used = 0;
	if (type == 1 && c == '<' && used == 0)
		used++;
	else if (type == 2 && c == '>' && used == 0)
		used++;
	else if (type == 3 && c == '|' && used == 0)
		used++;
	else if (type == 4 && c == '"')
		used++;
	else if (type == 5 && c == 39)
		used++;
	if (used <= 2)
		return (1);
	return (0);
}
