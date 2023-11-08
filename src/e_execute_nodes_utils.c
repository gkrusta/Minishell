#include "minishell.h"

void	exec_built(t_cmd *node, t_shell *shell, int stdoutcpy)
{
	dup2(node->outfile, STDOUT_FILENO);
	if (ft_strcmp(node->cmd, "env") == 0)
		print_env_variables(shell, shell->env_lst);
	if (strcmp(node->cmd, "export") == 0)
		export(shell, node->args);
	if (strcmp(node->cmd, "echo") == 0)
		echo(shell, node->args);
	if (strcmp(node->cmd, "cd") == 0)
		cd(shell, node->args);
	if (strcmp(node->cmd, "unset") == 0)
		unset(shell, node->args);
	if (strcmp(node->cmd, "pwd") == 0)
		pwd(shell);
	close(node->outfile);
	dup2(stdoutcpy, STDOUT_FILENO);
	dup2((node->outfile - 1), STDIN_FILENO);
	close((node->outfile - 1));
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

void	restore_std(t_cmd *node, int stdincpy, int stdoutcpy)
{
	dup2(stdincpy, STDIN_FILENO);
	dup2(stdoutcpy, STDOUT_FILENO);
	//close(node->outfile);
	//close(node->outfile - 1);
	//close (node->infile);
	close(stdincpy);
	close(stdoutcpy);
}

void	cmd_error_msg(t_cmd *node, t_shell *shell)
{
	if (node->cmd[0] == '\0')
		ft_printf("%s: command not found\n", node->args[0]);
	if (node->cmd[0] == '/')
		ft_printf("%s: command not found\n", node->cmd);
	shell->exit_status = 127;
}
