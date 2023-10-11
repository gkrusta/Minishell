/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:01:05 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/11 16:58:18 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>

#include "../assets/libft/libft.h"

// structura que va a tener cada commando despues de lexer
typedef struct		s_cmd
{
	char			*cmd; // solo commando
	char			*cmd_path; // commando + su path
	int				infile;
	int				outfile;
	struct s_cmd	*next; // apunta al siguiente commando
}					t_cmd;

// para guardar el path
/* typedef struct		s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp; */

typedef struct		s_shell
{
	char			**env_copy; // copia de varibles entornos
	t_list			*env_lst_copy;  // copia de varibles entornos
}					t_shell;

/* p_env */
char	*ft_strndup(const char *str, size_t len);
char	**ft_strddup(const char **envp);
void	create_env_lst(t_shell *shell, char **envp);
void	print_env_variables(t_list *env);
void	free_params(t_shell *shell);


#endif