/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:01:05 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/23 20:29:58 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
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
void	delete_value(t_shell *shell, int node_pos);
void	free_node(t_list *node);

// b_echo.c
int 	echo(t_shell *shell, char **args);
void	print_echo(char **tokens, int i);
int 	put_space(char **tokens, int i);

// b_cd.c
void	cd(t_shell *shell, char **args);
void	only_cd(t_shell *shell);
void	last_cd(t_shell *shell);
void	free_args(char **args);
void	abs_path(t_shell *shell, char *path);
void	home_cd(t_shell *shell, char *path);
// b_cd_utils.c
void	free_args(char **args);
char	*get_value(t_shell *shell, char *key);
void	ft_export_pwds(t_shell *shell, char *old_dir, char *new_dir);
//b_pwd.c
void	pwd(t_shell *shell);

/* b_env */
char	*ft_strndup(const char *str, size_t len);
char	**ft_strddup(const char **envp);
void	create_env_lst(t_shell *shell, char **envp);
void	print_env_variables(t_list *env);
void	free_params(t_shell *shell);

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