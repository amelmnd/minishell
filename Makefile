# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 14:10:33 by amennad           #+#    #+#              #
#    Updated: 2023/10/15 13:06:28 by nstoutze         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLOR MAKEFILE
COLOR_GREEN=\033[0;32m
COLOR_RED=\033[0;31m
COLOR_BLUE=\033[0;36m
COLOR_YELLOW = \033[0;93m
COLOR_MAGENTA = \033[0;95m
END_COLOR=\033[0m

# VAR
NAME = minishell
ORIGIN = main.c
CC = cc
INCLUDE = ./include/libft/libft.a -lreadline -L /Users/work/.brew/Cellar/readline/8.2.1/lib -I /Users/work/.brew/Cellar/readline/8.2.1/include
CFLAGS = -Wall -Wextra -Werror -I ./include

# DEBUG
DCFLAGS_VAL = $(CFLAGS) -g
DCFLAGS_FSA = $(CFLAGS) -g3 -fsanitize=address


PATH_LEX = $(addprefix $(DIR_LEX), $(SRCS_LEX))
DIR_LEX = lexer/
SRCS_LEX = lexer.c\

PATH_PARS = $(addprefix $(DIR_PARS), $(SRCS_PARS))
DIR_PARS = parser/
SRCS_PARS = parser.c\

PATH_EXP = $(addprefix $(DIR_EXP), $(SRCS_EXP))
DIR_EXP = expander/
SRCS_EXP = expander.c\
		   exp_list_generator_del.c \
		   print_exp_list_del.c \
		   gen_random_str_del.c \
		   msh_random_del.c \
		   exp_list_node_management_del.c \
		   msh_del.c \
		   feed_msh_acavenvp_del.c \

PATH_EXEC = $(addprefix $(DIR_EXEC), $(SRCS_EXEC))
DIR_EXEC = exec/
SRCS_EXEC = exec.c\
			build_exec_list_del.c \
			print_exec_list_del.c \
			init_exec_list_node_management_del.c \
			exec_list_node_data_del.c \
			pipe_fork_close_dup2_del.c \
			new_exec.c \

PATH_BUIL = $(addprefix $(DIR_BUIL), $(SRCS_BUIL))
DIR_BUIL = builtins/
SRCS_BUIL = builtins.c\

PATH_UTILS = $(addprefix $(DIR_UTILS), $(SRCS_UTILS))
DIR_UTILS = utils/
SRCS_UTILS = utils.c \
			 get_next_line.c \
			 get_next_line_utils.c \
			 ft_strcmp.c \

SRCS = $(PATH_UTILS) $(PATH_LEX) $(PATH_PARS) $(PATH_EXP) $(PATH_EXEC) $(PATH_BUIL)  $(ORIGIN)

OBJS = $(SRCS:.c=.o)

# RULES
# Executor
all: $(NAME)

libft:
	@make -C ./include/libft

$(NAME): $(OBJS) libft
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)
	@echo "$(COLOR_MAGENTA)objs & $(NAME) generate 🌸$(END_COLOR)"

run: libft
	@$(CC) $(CFLAGS) $(SRCS) $(INCLUDE) -o $(NAME)
	@echo "$(COLOR_GREEN)$(NAME) generate 🍀$(END_COLOR)"

# Debug
debugv : $(OBJS) libft
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)
	valgrind --leak-check=full ./minishell

debugfa: run
	@$(CC) $(DCFLAGS_FSA) -g3 -fsanitize=address $(SRCS) $(INCLUDE) -o $(NAME)
	./$(NAME)

# Clean
clean:
	@cd ./include/libft; make clean
	@rm -rf $(OBJS)
	@echo "$(COLOR_BLUE) clean 🐟$(END_COLOR)"

fclean : clean
	@cd ./include/libft && make fclean
	@rm -rf $(NAME)
	@echo "$(COLOR_BLUE) fclean 🐳$(END_COLOR)"

re:fclean all
	@echo "$(COLOR_MAGENTA)make re OK 🌸$(END_COLOR)"

.PHONY: all clean fclean re run libft debug_val debug_fa
