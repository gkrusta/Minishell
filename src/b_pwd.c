/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvilchez <pvilchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:55:17 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/28 12:49:22 by pvilchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_shell *shell)
{
	if (getcwd(shell->path, 128) != NULL)
		ft_printf("%s\n", shell->path);
	else
	{
		perror(shell->path);
		shell->exit_status = errno;
	}
}
