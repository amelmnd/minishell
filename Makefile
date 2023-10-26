# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amennad <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 14:10:33 by amennad           #+#    #+#              #
#    Updated: 2023/10/26 11:08:40 by amennad          ###   ########.fr        #
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
SRCS_LEX =	lexer.c lexer_list_manage.c create_lexer_list.c is_bracket.c is_other_operator.c is_quote.c is_dollar.c is_word.c\

PATH_PARS = $(addprefix $(DIR_PARS), $(SRCS_PARS))
DIR_PARS = parser/
SRCS_PARS = parser.c limit_is_valid.c check_valide_next.c\

PATH_EXP = $(addprefix $(DIR_EXP), $(SRCS_EXP))
DIR_EXP = expander/
SRCS_EXP = expander.c check_var_value.c\

PATH_EXEC = $(addprefix $(DIR_EXEC), $(SRCS_EXEC))
DIR_EXEC = exec/
SRCS_EXEC = exec.c\

PATH_BUIL = $(addprefix $(DIR_BUIL), $(SRCS_BUIL))
DIR_BUIL = builtins/
SRCS_BUIL = builtins.c\

PATH_UTILS = $(addprefix $(DIR_UTILS), $(SRCS_UTILS))
DIR_UTILS = utils/
SRCS_UTILS =	utils.c\
				manage_error.c\
				free_list.c\
				fn_env.c\
				fn_env_list.c\

# TODO DELETE
PATH_DEV = $(addprefix $(DIR_DEV), $(SRCS_DEV))
DIR_DEV = for_dev/
SRCS_DEV = dev_color.c dev_print_lexer_list.c dev_print_exp_list.c dev_print_env_list.c\

SRCS = $(PATH_UTILS) $(PATH_LEX) $(PATH_PARS) $(PATH_EXP) $(PATH_EXEC) $(PATH_BUIL) $(PATH_DEV) $(ORIGIN)

OBJS = $(SRCS:.c=.o)

# RULES
# Executor
all: $(NAME)

libft:
	@make -C ./include/libft

$(NAME): $(OBJS) libft
	@$(CC) $(INCLUDE) $(CFLAGS)  $(OBJS) -o $(NAME)
	@echo "$(COLOR_MAGENTA)objs & $(NAME) generate 🌸$(END_COLOR)"

run: libft
	@$(CC) $(CFLAGS) $(INCLUDE) $(SRCS) -o $(NAME)
	@echo "$(COLOR_GREEN)$(NAME) generate 🍀$(END_COLOR)"

norme:
	norminette $(PATH_UTILS) $(PATH_LEX) $(PATH_PARS) $(PATH_EXP) $(PATH_EXEC) $(PATH_BUIL) $(ORIGIN)

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
