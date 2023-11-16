/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execute_nodes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:26:03 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/16 16:57:40 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_invalid(char *cmd_old, char *cmd_new)
{
	if (ft_strcmp(cmd_old, cmd_new))
	{
		if (!ft_strcmp("export", cmd_new) || !ft_strcmp("unset", cmd_new))
			return (1);
		else
			return (0);
	}
	return (0);
}

void	exec_built(t_cmd *node, t_shell *shell, int stdoutcpy)
{
	char	*cmd;

	cmd = ft_strdup(node->cmd);
	node->cmd = convert_lowercase(cmd);
	if (!built_invalid(cmd, node->cmd))
	{
		dup2(node->outfile, STDOUT_FILENO);
		if (ft_strcmp(node->cmd, "env") == 0)
		{
			if (!shell->env_path)
				cmd_error_msg(node, shell, cmd);
			else
				print_env_variables(shell, shell->env_lst);
		}
		if (ft_strcmp(node->cmd, "export") == 0)
			export(shell, node->args);
		if (ft_strcmp(node->cmd, "echo") == 0)
			echo(shell, node->args);
		if (ft_strcmp(node->cmd, "cd") == 0)
			cd(shell, node->args[0]);
		if (ft_strcmp(node->cmd, "unset") == 0)
			unset(shell, node->args);
		if (ft_strcmp(node->cmd, "pwd") == 0)
			pwd(shell);
		dup2(stdoutcpy, STDOUT_FILENO);
		dup2((node->outfile - 1), STDIN_FILENO);
		close(node->outfile);
		close((node->outfile - 1));
	}
	else
		cmd_error_msg(node, shell, "42");
	free(cmd);
}

int	check_absolut(t_cmd *node)
{
	char	*str;
	int		i;

	i = 0;
	if (node->cmd[0] == '\0' && node->args[0])
	{
		if (node->args[0][0] == '/')
		{
			str = ft_strrchr(node->args[0], '/');
			free(node->cmd);
			node->cmd = ft_strdup(&str[1]);
			free(node->cmd_path);
			node->cmd_path = ft_strdup(node->args[0]);
			while (i < 9)
			{
				node->args[i] = node->args[i + 1];
				i++;
			}
			return (1);
		}
	}
	return (0);
}

void	restore_std(int stdincpy, int stdoutcpy)
{
	int	i;

	dup2(stdincpy, STDIN_FILENO);
	dup2(stdoutcpy, STDOUT_FILENO);
	close(stdincpy);
	close(stdoutcpy);
	i = 3;
	while (i < 50)
	{
		close(i);
		i++;
	}
}

void	cmd_error_msg(t_cmd *node, t_shell *shell, char *cmd)
{
	if (!ft_strcmp(cmd, "42"))
	{
		if (node->cmd[0] == '\0' && node->args[0])
			ft_printf("minshell: %s: command not found\n", node->args[0]);
		else if (node->cmd[0] == '/')
			ft_printf("minshell: %s: command not found\n", node->cmd);
		else
			ft_printf("minshell: %s: No such file or directory\n", node->cmd);
	}
	else
		ft_printf("minshell: %s: No such file or directory\n", cmd);
	shell->exit_status = 127;
}
