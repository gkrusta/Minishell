# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pvilchez <pvilchez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 13:19:25 by pvilchez          #+#    #+#              #
#    Updated: 2023/10/27 13:12:22 by pvilchez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -g #-fsanitize=address
CFLAGS = -Wall -Wextra -Werror 
REMOVE = rm -rf
LREADLINE = -lreadline

OBJ_PATH = obj
SRC_PATH = src
INC_PATH = include

LIBFT_PATH = assets/libft
LIBFT_LIB_PATH = assets/libft/libft.a

HEADERS	= -I $(LIBFT_PATH)/include/ -I ./include

SRC_FILES = b_cd_utils.c b_cd.c b_echo.c b_env_utils.c b_env.c \
			b_export_utils_b.c b_export_utils.c b_export.c b_pwd.c b_unset.c \
			e_execute_nodes.c e_make_nodes_utils.c e_make_nodes.c \
			e_nodes_utils.c e_path_utils.c e_signals.c \
			mini_args.c minishell.c \
			p_dbg_print.c p_dollar_sign.c p_split_utils.c p_split.c p_trim.c \
			r_redir_heredoc.c r_redir.c
			   
SRC := $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

ORANGE = \033[1;38;5;208m
RESET = \033[0m
U_LINE = \033[4m
YELLOW = \033[1;38;5;226m

all: $(LIBFT_LIB_PATH) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIBFT_LIB_PATH) $(HEADERS) $(LREADLINE) -o $@
	@echo "\n$(ORANGE)$(U_LINE)$(NAME): Mandatory Compiled$(RESET) \n"

$(LIBFT_LIB_PATH):
	@$(MAKE) -C $(LIBFT_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@echo "$(YELLOW)$(NAME) Compiling:$(RESET) $(notdir $<)"

clean:
	@$(REMOVE) $(OBJ_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	@$(REMOVE) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re $(LIBFT_LIB_PATH)