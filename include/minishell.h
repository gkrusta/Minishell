/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvilchez <pvilchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:01:05 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/02 18:02:12 by pvilchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700 // para compilar signals en linux

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <termios.h>

#include "../assets/libft/libft.h"
#include "minishell_defines.h"
#include "minishell_structs.h"


extern int shell_state;

// minishell.c

// mini_args.c
void	mini_args(int argc, char *argv[], int *mode);
// p_split.c
char	**p_split(char *input, t_shell *shell);
int		ft_isspace(char c);
// p_split_utils.c
int		assign_type(char c);
int		end_token(char c, int type, int *used);
void	free_tokens(t_shell *shell);
// p_dbg_print.c
void	dbg_print_array_tokens(char **tokens, int mode, t_shell *shell);
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
int		check_key(char *key, int print, t_shell *shell, char *str);
// b_unset.c
void	unset(t_shell *shell, char **args);
void	delete_value(t_shell *shell, int node_pos);
void	free_node(t_list *node);

// b_echo.c
int 	echo(t_shell *shell, char **args);
void	print_echo(t_shell *shell, char **tokens, int i);
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
void	create_env_lst(t_shell *shell, char **envp);
void	print_env_variables(t_shell *shell, t_list *env);
void	free_params(t_shell *shell);
int		key_search(t_list *env, char *str);
t_list	*node_search(t_list *env, char *str);
/* b_env_utils */
char	*check_level(char *lvl);
void	update_level(t_shell *shell, int flag);
void	parse_env(t_shell *shell, char **envp);
char	*ft_strndup(const char *str, size_t len);
char	**ft_strddup(const char **envp);
/* b_env_update.c */
void	update_env(t_shell *shell);
char	**ft_stddup_env(t_shell *shell);
char	*concat_env(t_list *env_lst_cpy, char **env, int pos);
int		count_env_var(t_shell *shell);
// e_make_nodes.c
void	make_nodes(t_shell *shell, char *input, int mode);
// e_make_nodes_utils.c
int		is_built_in(char *token);
void	check_redir(t_cmd *node, char **tokens, int *i, int *fd);
char	*str_change_value(char *old_str, char *new_str);
// e_path_utils.c
char	*find_path(char *command, char **envp, char *empty_str);
int		is_in_path(t_shell *shell, char *str);
// e_nodes_utils.c
void	ft_add_front_node(t_cmd **lst, t_cmd *new_node);
void	ft_add_back_node(t_cmd **lst, t_cmd *new_node);
void	lst_clear_nodes(t_cmd **lst);
t_cmd	*lst_new_node(void);
// e_execute_nodes.c
void	execute_nodes(t_cmd **nodes, t_shell *shell);
// e_execute_nodes_utils.c
int		check_absolut(t_cmd *node);
// e_signals.c
void	signal_handler(int signal);
void	setup_signal_handling(void);
// r_redir.c
void	token_pipe(t_cmd *node, int *fd, int *fd_in);
void	token_input(char **tokens, int *i, t_cmd *node);
void	token_output(char **tokens, int *i, t_cmd *node);
void	token_output_cat(char **tokens, int *i, t_cmd *node);
// r_redir_heredoc.c
void	token_heredoc(char **tokens, int *i, t_cmd *node);
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