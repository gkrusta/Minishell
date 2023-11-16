/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execute_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:25:58 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/16 16:52:14 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_mini(t_cmd *node)
{
	if (node->args[0] != NULL)
	{
		if (ft_strlen(node->args[0]) >= 2)
		{
			if (node->args[0][0] == '.' && node->args[0][1] == '/')
				return (1);
		}
	}
	return (0);
}

void	exec_comm(t_cmd *node, t_shell *shell)
{
	int	i;

	i = 8;
	while (i > 0)
	{
		node->args[i] = node->args[i - 1];
		i--;
	}
	if (new_mini(node))
		execve(node->args[0], &node->args[1], shell->env);
	node->args[0] = node->cmd;
	execve(node->cmd_path, node->args, shell->env);
}

void	fork_child(t_cmd *node, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (new_mini(node))
			update_level(shell, 1);
		dup2(node->outfile, STDOUT_FILENO);
		exec_comm(node, shell);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	dup2((node->outfile - 1), STDIN_FILENO);
	close(node->outfile);
	close((node->outfile - 1));
}

int	run_node(t_cmd *node, t_shell *shell)
{
	if (is_built_in(node->cmd))
		exec_built(node, shell, shell->stdoutcpy);
	else if (node->cmd_path[0] == '\0' || node->cmd[0] == '/')
	{
		if (new_mini(node))
		{
			dup2(shell->stdincpy, STDIN_FILENO);
			fork_child(node, shell);
			return (1);
		}
		dup2(shell->stdoutcpy, STDOUT_FILENO);
		cmd_error_msg(node, shell, "42");
		return (1);
	}
	else
		fork_child(node, shell);
	return (0);
}

void	execute_nodes(t_cmd **nodes, t_shell *shell)
{
	t_cmd	*node;
	int		i;

	shell->stdincpy = dup(STDIN_FILENO);
	shell->stdoutcpy = dup(STDOUT_FILENO);
	node = *nodes;
	dup2(node->infile, STDIN_FILENO);
	while (node && g_shell_state != 3)
	{
		i = check_absolut(node);
		if (run_node(node, shell) && node->next == NULL)
			break ;
		if (i == 1)
			free(node->cmd);
		node = node->next;
	}
	if (g_shell_state == 3)
		shell->exit_status = 130;
	node = *nodes;
	restore_std(shell->stdincpy, shell->stdoutcpy);
}
