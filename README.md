# Minishell

This project is a simple shell implementation written in C, with features such as command execution, built-in commands, and signal handling.

## Project Structure
```
minishell-project
│
├── Makefile
├── assets
│   └── libft
│       ├── Makefile
│       ├── ft_isalnum.c
│       ├── ft_long_atoi.c
│       ├── ft_memchr.c
│       ├── ft_putchar.c
│       ├── ... (other libft source files)
│       └── libft.h
├── include
│   ├── minishell.h
│   └── minishell_structs.h
└── src
    ├── b_cd.c
    ├── b_env.c
    ├── b_exit.c
    ├── b_export_utils_b.c
    ├── ... (other source files)
    └── r_redir.c
``````
## Usage

To compile the project, use the provided `Makefile`. Run the following command:
```
make
