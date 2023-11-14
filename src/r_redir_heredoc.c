/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_redir_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvilchez <pvilchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:23:49 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/14 18:41:37 by pvilchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			line = readline("> ");
			if (!line)
				break ;
			if (ft_strncmp(line, tok[*i + 1], ft_strlen(tok[*i + 1]) + 1) == 0)
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
