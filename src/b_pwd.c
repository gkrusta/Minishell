/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:55:17 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/20 15:21:15 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_shell *shell)
{
	if (getcwd(shell->path, 128) != NULL)
		printf("%s\n", shell->path);
	else
	{
		perror(shell->path);
		shell->exit_status = errno;
	}
}
