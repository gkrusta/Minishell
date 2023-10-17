#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

// structura que va a tener cada commando despues de lexer
typedef struct		s_cmd
{
	char			*cmd; // solo commando
	char			*cmd_path; // commando + su path
	int				infile;
	int				outfile;
	struct s_cmd	*next; // apunta al siguiente commando
}					t_cmd;

typedef struct		s_shell
{
	char			**env; // copia de varibles entornos
	t_list			*env_lst;  // copia de varibles entornos
	char			**tokens;
	int				exit_status;
}					t_shell;

// para guardar el path
/* typedef struct		s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp; */

// estructura que hay en libft
/*typedef struct		s_list
{
	void			*key;
	void			*value;
	struct s_list	*next;
}					t_list;
*/
#endif