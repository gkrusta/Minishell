/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvilchez <pvilchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:01:05 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/12 17:54:06 by pvilchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>

#include "../assets/libft/libft.h"
#include "minishell_defines.h"
#include "minishell_structs.h"

// mini_args.c
void	mini_args(int argc, char *argv[], int *mode);
// p_split.c
char	**p_split(char *input);
int		ft_isspace(char c);
// p_split_utils.c
int		assign_type(char c);
int		end_token(char c, int type, int *used);
void	free_tokens(t_shell *shell);
// p_dbg_print.c
void	dbg_print_array_tokens(char **tokens, int mode);
// b_export.c
void	export(t_shell *shell, char **args);
// b_export_utils.c
void	free_arg(char *arg_key, char *arg_value);

/* p_env */
char	*ft_strndup(const char *str, size_t len);
char	**ft_strddup(const char **envp);
void	create_env_lst(t_shell *shell, char **envp);
void	print_env_variables(t_list *env);
void	free_params(t_shell *shell);


#endif