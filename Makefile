# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 14:10:33 by amennad           #+#    #+#              #
#    Updated: 2023/11/20 15:26:19 by nstoutze         ###   ########.fr        #
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
SRCS_LEX =	lexer.c \
			lexer_list_manage.c \
			create_lexer_list.c \
			is_bracket.c \
			is_other_operator.c \
			is_quote.c \
			is_dollar.c \
			is_word.c \

PATH_PARS = $(addprefix $(DIR_PARS), $(SRCS_PARS))
DIR_PARS = parser/
SRCS_PARS = parser.c \
			limit_is_valid.c \
			check_valide_next.c \

PATH_EXP = $(addprefix $(DIR_EXP), $(SRCS_EXP))
DIR_EXP = expander/
SRCS_EXP = expander.c \
		   exp_list_generator_del.c \
		   print_exp_list_del.c \
		   gen_random_str_del.c \
		   exp_list_node_management_del.c \
		   feed_msh_acavenvp_del.c \
		   check_var_value.c \
		   expander_list_manage.c \
		   create_expander_list.c \
		   ft_join_words.c \
		   var_transform.c \

PATH_EXEC = $(addprefix $(DIR_EXEC), $(SRCS_EXEC))
DIR_EXEC = exec/
SRCS_EXEC = build_exec_list/assign_pos_ppl_exec_list.c \
			build_exec_list/build_exec_list.c \
			build_exec_list/exec_list_node_management.c \
			build_exec_list/feed_exec_list_node.c \
			build_exec_list/feed_exec_list_nodes_cmd.c \
			build_exec_list/feed_exec_list_nodes_data.c \
			build_exec_list/feed_the_only_exec_list_node_data.c \
			build_exec_list/get_nb_pipes_in_exp_list.c \
			build_exec_list/malloc_exec_list_node_arrays.c \
			build_exec_list/scan_redirects.c \
			execution/check_cmd_path_n_exec.c \
			execution/do_all_redirections.c \
			execution/do_redir.c \
			execution/exec.c \
			execution/new_exec.c \
			execution/pid_t_array.c \
			here_doc/feed_append_new_hd_node.c \
			here_doc/get_all_hd_content.c \
			here_doc/get_hd.c \
			here_doc/get_hd_in_exec_list_node.c \
			here_doc/hd_send_pipe.c \
			here_doc/mark_all_erased_hd.c \
			here_doc/new_hd.c \
			solo_builtin/builtin_solo_without_fork.c \
			solo_builtin/do_all_redir_solo_builtin.c \

PATH_BUIL = $(addprefix $(DIR_BUIL), $(SRCS_BUIL))
DIR_BUIL = builtins/
SRCS_BUIL = cd/cd_builtin.c \
			cd/update_oldpwd_n_pwd.c \
			export/export_builtin.c \
			export/export_without_args.c \
			export/export_without_args_utils.c \
			export/export_get_var_name.c \
			export/is_a_valid_identifier.c \
			export/add_new_couple_name_value.c \
			export/update_variable.c \
			export/export_get_var_value.c \
			export/add_var_to_env_list.c \
			export/export_with_args.c \
			unset/unset_builtin.c \
			unset/remove_from_env_list.c \
			builtins.c \
			echo_builtin.c \
			env_builtin.c \
			exit_builtin.c \
			pwd_builtin.c \

PATH_UTILS = $(addprefix $(DIR_UTILS), $(SRCS_UTILS))
DIR_UTILS = utils/
SRCS_UTILS = utils.c \
			 malloc_full_null_charss.c \
			 generate_msh_env.c \
			 show_no_args_for_minishell_error_msg.c \
			 reset_counts.c \
			 get_next_line.c \
			 is_chr_in_str.c \
			 get_next_line_utils.c \
			 ft_strcmp.c \
			 get_size_env_list.c \
			 free_chars.c \
			 manage_error.c \
			 ft_execve.c \
			 free_msh.c \
			 errmsg_free_exit.c \
			 free_ints.c \
			 build_user_for_prompt.c \
			 new_msh.c \
			 free_list.c \
			 fn_env.c \
			 fn_env_list.c \
			 adapt_libft.c \
			 print_charss_del.c \
			 free_ntcharss.c \

# TODO DELETE
PATH_DEV = $(addprefix $(DIR_DEV), $(SRCS_DEV))
DIR_DEV = for_dev/
SRCS_DEV = dev_color.c \
		   dev_print_lexer_list.c \
		   dev_print_exp_list.c \
		   dev_print_env_list.c\
		   dev_print_pid_t_array.c \
		   print_exec_list_del.c \

SRCS = $(PATH_UTILS) $(PATH_LEX) $(PATH_PARS) $(PATH_EXP) $(PATH_EXEC) $(PATH_BUIL) $(PATH_DEV) $(ORIGIN)

OBJS = $(SRCS:.c=.o)

## RULES
## Executor
#all: $(NAME)
#
#libft:
#	@make -C ./include/libft
#
#$(NAME): $(OBJS) libft
#	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)
#	@echo "$(COLOR_MAGENTA)objs & $(NAME) generate 🌸$(END_COLOR)"


# RULES
all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "compiling : $<                                      \r"

libft:
	@make -C ./include/libft

$(NAME): $(OBJS) libft
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)
	@echo "$(COLOR_MAGENTA)objs & $(NAME) generate 🌸$(END_COLOR)"

run: libft
	@$(CC) $(CFLAGS) $(SRCS) $(INCLUDE) -o $(NAME)
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
