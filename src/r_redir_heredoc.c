/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_redir_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:23:49 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/20 10:46:32 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_heredoc(char **tok, int *i, t_cmd *node)
{
	int		fd[2];
	char	*line;

	g_shell_state = 5;
	line = NULL;
	printf("node cmd is %s\n", node->cmd);
	if (tok[*i + 1])
	{
		pipe(fd);
		while (1 && g_shell_state != 3)
		{
			write(STDOUT_FILENO, "> ", 2);
			line = get_next_line(0);
			if (!line && node->cmd == NULL)
			{
				g_shell_state = 6;
				break ;
			}
			if (ft_strncmp(line, tok[*i + 1], ft_strlen(tok[*i + 1]) + 1) == 10)
				break ;
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
		if (g_shell_state != 3)
			free(line);
		close(fd[1]);
		node->infile = fd[0];
		*i = *i + 1;
	}
}
