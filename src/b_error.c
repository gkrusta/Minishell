/* void	ft_error_msg(char *str, shell)
{
	perror(str);
	shell->exit_status = 1;
}
 */
void	command_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": pipex: command not found", 2);
	exit(127);
}
