/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execute_nodes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:26:03 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/20 17:21:51 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_valid(t_cmd *node, t_shell *shell, int stdoutcpy, char *old_cmd)
{
	dup2(node->outfile, STDOUT_FILENO);
	if (ft_strcmp(node->cmd, "env") == 0)
	{
		if (!shell->env_path)
			cmd_error_msg(node, shell, old_cmd);
		else
			print_env_variables(shell, shell->env_lst);
	}
	else if (ft_strcmp(node->cmd, "export") == 0)
		export(shell, node->args);
	else if (ft_strcmp(node->cmd, "echo") == 0)
		echo(shell, node->args);
	else if (ft_strcmp(node->cmd, "cd") == 0)
		cd(shell, node->args[0]);
	else if (ft_strcmp(node->cmd, "unset") == 0)
		unset(shell, node->args);
	else if (ft_strcmp(node->cmd, "pwd") == 0)
		pwd(shell);
	dup2(stdoutcpy, STDOUT_FILENO);
	dup2((node->outfile - 1), STDIN_FILENO);
	close(node->outfile);
	close((node->outfile - 1));
}

void	exec_built(t_cmd *node, t_shell *shell, int stdoutcpy)
{
	char	*old_cmd;

	old_cmd = ft_strdup(node->cmd);
	free(node->cmd);
	node->cmd = convert_lowercase(old_cmd);
	if (!built_invalid(old_cmd, node->cmd))
		built_valid(node, shell, stdoutcpy, old_cmd);
	else if (built_invalid(old_cmd, node->cmd) == 1)
		cmd_error_msg(node, shell, old_cmd);
	free(old_cmd);
}

int	check_absolut(t_cmd *node)
{
	char	*str;
	int		i;

	i = 0;
	if (node->cmd[0] == '\0' && node->args[0])
	{
		if (node->args[0][0] == '/' && access(node->args[0], X_OK) == 0)
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
	if (!shell->env_path)
	{
		ft_printf("minshell: %s: No such file or directory\n", cmd);
		shell->exit_status = 127;
	}
	else if (node->args[0] && node->cmd)
	{
		if (node->args[0][0] == '/')
			ft_printf("minshell: %s: No such file or directory\n",
				node->args[0]);
		else if (node->cmd[0] == '\0' && node->args[0])
			ft_printf("minshell: %s: command not found\n", node->args[0]);
		else
			ft_printf("minshell: %s: No such file or directory\n", node->cmd);
		shell->exit_status = 127;
	}
}
