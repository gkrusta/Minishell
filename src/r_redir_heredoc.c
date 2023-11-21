/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_redir_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:23:49 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/21 14:42:38 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_line_cleanup(char *line, int fd[2], t_cmd *node, int *i)
{
	if (g_shell_state != 3)
		free(line);
	(void)line;
	close(fd[1]);
	node->infile = fd[0];
	*i = *i + 1;
}

void	token_heredoc(char **tok, int *i, t_cmd *node)
{
	int		fd[2];
	char	*line;

	g_shell_state = 5;
	line = NULL;
	if (tok[*i + 1])
	{
		pipe(fd);
		while (1 && g_shell_state != 3)
		{
			write(STDOUT_FILENO, "> ", 2);
			line = get_next_line(0);
			if (!line)
			{
				if (!node->cmd)
					g_shell_state = 2;
				break ;
			}
			if (ft_strncmp(line, tok[*i + 1], ft_strlen(tok[*i + 1]) + 1) == 10)
				break ;
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
		read_line_cleanup(line, fd, node, i);
	}
}
