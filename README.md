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
## Installation:

1. **Clone the Repository**:

```bash
git clone https://github.com/gkrusta/Minishell minishell
```

2. **Build the Project**:

```bash
cd minishell && make
```

3. **Run the Server**:

```bash
./Minishell
```

### Teammate: 🦍   [pvilchez](https://github.com/pablovilchez)
