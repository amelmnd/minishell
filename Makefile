# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amennad <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 14:10:33 by amennad           #+#    #+#              #
#    Updated: 2023/11/25 17:20:07 by amennad          ###   ########.fr        #
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

PATH_LEX = $(addprefix $(DIR_LEX), $(SRCS_LEX))
DIR_LEX = lexer/
SRCS_LEX = create_lexer_list.c \
		   is_bracket.c \
		   is_dollar.c \
		   is_other_operator.c \
		   is_quote.c \
		   is_word.c \
		   lexer.c \
		   lexer_list_manage.c \

PATH_PARS = $(addprefix $(DIR_PARS), $(SRCS_PARS))
DIR_PARS = parser/
SRCS_PARS = check_valide_next.c \
			limit_is_valid.c \
			parser.c \

PATH_EXP = $(addprefix $(DIR_EXP), $(SRCS_EXP))
DIR_EXP = expander/
SRCS_EXP = check_var_value.c \
		   create_expander_list.c \
		   expander.c \
		   musical_chairs.c \
		   expander_fn.c \
		   expander_list_manage.c \
		   ft_join_words.c \
		   var_transform.c \
		   that_is_variable.c \
		   is_element.c \

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
			execution/builtin_way.c \
			execution/check_cmd_path_n_exec.c \
			execution/do_all_redirections.c \
			execution/do_redir.c \
			execution/exec.c \
			execution/ft_execve.c \
			execution/get_paths_from_path.c \
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
			exit/contains_non_sign_or_num_chr.c \
			exit/easy_tests.c \
			exit/exit_builtin.c \
			exit/front_zeros_stripped_parsing.c \
			exit/get_htss.c \
			exit/ht_spaces_stripped_parsing.c \
			exit/limits_single_shortcuts.c \
			exit/more_than_one_sign.c \
			exit/non_numeric_arg_assignation.c \
			exit/normal_cases_exit_atoi.c \
			unset/unset_builtin.c \
			unset/remove_from_env_list.c \
			echo_builtin.c \
			env_builtin.c \
			pwd_builtin.c \

PATH_UTILS = $(addprefix $(DIR_UTILS), $(SRCS_UTILS))
DIR_UTILS = utils/
SRCS_UTILS = before_prompt_loop/build_user_for_prompt.c \
			 before_prompt_loop/new_msh.c \
			 before_prompt_loop/show_no_args_for_minishell_error_msg.c \
			 environment_management/feed_env_list_node.c \
			 environment_management/fn_env.c \
			 environment_management/env_list_generate.c \
			 environment_management/generate_msh_env.c \
			 environment_management/get_index_first_equal.c \
			 environment_management/get_size_env_list.c \
			 environment_management/split_env_value.c \
			 error_msg/ambiguous_redirect_errmsg.c \
			 error_msg/print_cmd_not_found_errormsg.c \
			 error_msg/exit_command_not_foud.c \
			 error_msg/exit_no_file_directory.c \
			 error_msg/exit_synthax_error.c \
			 error_msg/is_a_directory_errmsg.c \
			 free/errmsg_free_exit.c \
			 free/free_chars.c \
			 free/free_exec.c \
			 free/free_exec_list.c \
			 free/free_exit.c \
			 free/free_exp_list.c \
			 free/free_ints.c \
			 free/free_lexer_list.c \
			 free/free_list.c \
			 free/free_msh.c \
			 free/free_ntcharss.c \
			 generic/ft_msh_strchr.c \
			 generic/ft_strcmp.c \
			 generic/get_size_ntcharss.c \
			 generic/is_chr_in_str.c \
			 generic/malloc_full_null_charss.c \
			 generic/ntcharss_copy.c \
			 generic/reset_counts.c \
			 exit_new_line.c \
			 ft_signal.c \

SRCS = $(PATH_UTILS) $(PATH_LEX) $(PATH_PARS) $(PATH_EXP) $(PATH_EXEC) $(PATH_BUIL) $(ORIGIN)

OBJS = $(SRCS:.c=.o)

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

.PHONY: all clean fclean re run libft
