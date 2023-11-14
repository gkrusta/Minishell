/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:28:38 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/14 10:28:52 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef struct		s_cmd
{
	char			*cmd;
	char			*cmd_path;
	char			**args;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_shell
{
	char			**env;
	t_list			*env_lst;
	char			**tokens;
	int				exit_status;
	char			path[128];
	char			*space_next;
	int				lvl;
	int				fd_in;
	int				stdincpy;
	int				stdoutcpy;
}					t_shell;

#endif