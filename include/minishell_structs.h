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
	char			*path; // va a guardar el path
}					t_shell;


#endif