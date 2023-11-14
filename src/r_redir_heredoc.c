/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_redir_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:23:49 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/14 10:23:51 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_line(char **line)
{
	int		i;
	char	c;
	int		try_read;
	char	*read_line;

	i = 0;
	read_line = (char *)malloc(10000);
	if (!read_line)
		return (-1);
	ft_printf("> ");
	try_read = 0;
	try_read = read(0, &c, 1);
	while (try_read && c != '\n' && c != '\0' && shell_state != 3)
	{
		if (c != '\n' && c != '\0')
			read_line[i] = c;
		i++;
		try_read = read(0, &c, 1);
	}
	read_line[i] = '\n';
	read_line[++i] = '\0';
	*line = read_line;
	free(read_line);
	return (try_read);
}

void	token_heredoc(char **tokens, int *i, t_cmd *node)
{
	int		fd[2];
	char	*line;

	if (tokens[*i + 1])
	{
		pipe(fd);
		while (read_line(&line) && shell_state != 3)
		{
			if (ft_strncmp(line, tokens[*i +1], ft_strlen(tokens[*i +1])) == 0)
				break ;
			write(fd[1], line, ft_strlen(line));
		}
		node->infile = fd[0];
		close(fd[1]);
		*i = *i + 1;
	}
}
