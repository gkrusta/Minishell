#include "minishell.h"

void	check_path(t_shell *shell)
{
	ft_trim(shell);
	if (access(shell->tokens[1], F_OK) == 0)
	chdir
	if (chdir(shell->tokens[1]) != 0)
		perror("cd");
}

/* void	various_cd(t_shell *shell, char **args)
{

}

void	one_cd(t_shell *shell, char **args)
{
	
} */

void	cd(t_shell *shell, char **args)
{
	//char	*curr_path;
	int		i;
	char	64 getcwd

	//curr_path = getcwd(shell->path, 128);
	i = 0;
/* 	if (curr_path == NULL)
		printf( "An error occurred in the getcwd() function call.\n" ); */
/* 	if (!args[i])
		chdir() */
	while (args[i])
	{
		if (strcmp(args[0], "..") == 0)
		{
			char* current_dir = getcwd(NULL, 0);
			char* last_slash = ft_strrchr(current_dir, '/');
			if (last_slash != NULL)
				*last_slash = '\0';  // Remove the last directory in the path
			chdir(current_dir);
			//Actualizar (OLDPWD);
			//Actualizar (PWD)
			free(current_dir);
		}
		else if (strcmp(args[0], "/") == 0)
			chdir("/");
		else
			check_path(shell);

			//fprintf(stderr, "cd: %s: No such directory\n", argv[1]);
		i++;
	}
}

/* void	cd(t_shell *shell)
{
	printf ("\n\nThe actual directory is: %s\n",  getcwd (shell->path, 128));
	chdir( "/home/linuxhint/Documents/");
	printf ("\n\n The selected directory is: %s\n", getcwd (dir, 50));
} */