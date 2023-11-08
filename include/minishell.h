/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:01:05 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/08 15:26:44 by gkrusta          ###   ########.fr       */
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
void	p_split(char *input, t_shell *shell);
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
void	sort_array(char **str_array, int lst_size);
// b_unset.c
void	unset(t_shell *shell, char **args);
void	delete_value(t_shell *shell, int node_pos);
void	free_node(t_list *node);

// b_echo.c
int		echo(t_shell *shell, char **args);

// b_cd.c
void	cd(t_shell *shell, char **args);
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
void	check_redir(t_cmd *node, int *i, t_shell *shell, int plus);
char	*str_change_value(char *old_str, char *new_str);
void	init_values(t_shell *shell, int *i);
// e_path_utils.c
char	*find_path(char *command, char **envp, char *empty_str);
int		is_in_path(t_shell *shell, char *str);
// e_nodes_utils.c
void	ft_add_front_node(t_cmd **lst, t_cmd *new_node);
t_cmd	*ft_add_back_node(t_cmd **lst, t_cmd *new_node);
void	lst_clear_nodes(t_cmd **lst);
t_cmd	*lst_new_node(void);
// e_execute_nodes.c
void	execute_nodes(t_cmd **nodes, t_shell *shell);
// e_execute_nodes_utils.c
void	exec_built(t_cmd *node, t_shell *shell, int stdoutcpy);
int		check_absolut(t_cmd *node);
void	restore_std(t_cmd *node, int strincpy, int stdoutcpy);
void	cmd_error_msg(t_cmd *node, t_shell *shell);
// e_signals.c
void	signal_handler(int signal, char *input);
void	setup_signal_handling(struct sigaction *sa);
// r_redir.c
void	token_pipe(t_cmd *node, int *fd, t_shell *shell);
void	token_input(char **tokens, int *i, t_cmd *node);
void	token_output(char **tokens, int *i, t_cmd *node);
void	token_output_cat(char **tokens, int *i, t_cmd *node);
// r_redir_heredoc.c
void	token_heredoc(char **tokens, int *i, t_cmd *node);
/* $ */
int		varible_search(t_list *env_lst, char **var, int flag);
int		check_end(char *str, int pos);
char	*after_dolor_sign(t_shell *shell, char *str, int i);
char	*ft_concat(char *str, char *var, char *str_end, int *pos);
char	*str_after_var(char *str, int pos);
void	ft_token_check(t_shell *shell, char *str, int i);
int		is_inside_quotes(char *str, int pos);

/* p_trim.c */
void	ft_trim_tokens(t_shell *shell);
/* p_trim_utils.c */
char	*find_var(t_shell *shell, char *c, char *new_token, int *j);

#endif