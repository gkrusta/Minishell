/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvilchez <pvilchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:01:05 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/19 21:35:07 by pvilchez         ###   ########.fr       */
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

// minishell.c

// mini_args.c
void	mini_args(int argc, char *argv[], int *mode);
// p_split.c
char	**p_split(char *input);
int		ft_isspace(char c);
// p_split_utils.c
int		assign_type(char c);
int		end_token(char c, int type, int *used);
void	free_tokens(t_shell *shell);
// p_env
char	*ft_strndup(const char *str, size_t len);
char	**ft_strddup(const char **envp);
void	create_env_lst(t_shell *shell, char **envp);
void	print_env_variables(t_list *env);
void	free_params(t_shell *shell);
// p_dbg_print.c
void	dbg_print_array_tokens(char **tokens, int mode);
void	dbg_print_command_nodes(t_cmd **com_nodes, int mode);
// b_export.c
void	export(t_shell *shell, char **args);
void	extract_values(char *arg, t_list *new_arg);
int		key_found(char *arg_key, char *env_key, int *found);
void	create_key(t_list *env_list, t_list *new_arg);
void	copy_value(t_list *env_list, t_list *new_arg);
// b_export_utils.c
void	free_arg(t_list *new_arg);
void	export_empty(t_shell *shell);
// b_export_utils_b.c
int		check_key(char *key, int print, t_shell *shell);
// b_unset.c
void	unset(t_shell *shell, char **args);
// e_make_nodes.c
void	make_nodes(t_shell *shell, char *input, int mode);
// e_make_nodes_utils.c
int		is_built_in(char *token);
void	check_redir(t_cmd *node, char **tokens, int *i, int *fd);
void	str_change_value(char *old_str, char *new_str);
// e_path_utils.c
char	*find_path(char *command, char **envp);
int		is_in_path(t_shell *shell, char *str);
// e_nodes_utils.c
void	ft_add_front_node(t_cmd **lst, t_cmd *new_node);
void	ft_add_back_node(t_cmd **lst, t_cmd *new_node);
void	lst_clear_nodes(t_cmd **lst);
t_cmd	*lst_new_node(void);
// e_execute_nodes.c
void	execute_nodes(t_cmd **nodes);
// r_pipe.c
void	token_pipe(t_cmd *node, int *fd, int *fd_in);
void	token_input(char **tokens, int *i, t_cmd *node);
/* $ */
int 	varible_search(t_list *env_lst, char **var, int flag);
int		check_end(char *str, int pos);
char	*after_dolor_sign(t_shell *shell, char *str, int i);
char	*ft_concat(char *str, char *var, char *str_end, int *pos);
char	*str_after_var(char *str, int pos);
void	ft_token_check(t_shell *shell, char *str, int i);
int		is_inside_quotes(char *str, int pos);

/* trim "" '' */
int		ft_trim(t_shell *shell);
char	*trim_quotes(char *str);
int		pair_exists(char *str, char c);

#endif