# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/26 21:33:49 by nstoutze          #+#    #+#              #
#    Updated: 2023/07/03 22:26:09 by nstoutze         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = pipex

SRC = mandatory/main.c \
	  mandatory/pipex.c \
	  mandatory/new_ppx.c \
	  mandatory/initialize_ppx.c \
	  mandatory/ntcharss_copy.c \
	  mandatory/get_size_ntcharss.c \
	  mandatory/ft_strdup.c \
	  mandatory/ft_strlen.c \
	  mandatory/get_path_from_envp.c \
	  mandatory/get_paths_from_path.c \
	  mandatory/ft_split.c \
	  mandatory/free_chars.c \
	  mandatory/ft_substr.c \
	  mandatory/ft_strncmp.c \
	  mandatory/ft_strcmp.c \
	  mandatory/ft_strjoin.c \
	  mandatory/free_ppx.c \
	  mandatory/free_charss.c \
	  mandatory/errormsg_free_exit.c \
	  mandatory/cmd_parsing.c \
	  mandatory/build_slash_and_cmd.c \
	  mandatory/get_ac_av_envp_into_ppx.c \
	  mandatory/free_after_iteration.c \
	  mandatory/set_redirect.c \
	  mandatory/ft_close.c \
	  mandatory/ft_duptwo.c \
	  mandatory/ft_execve.c \
	  mandatory/ft_fork.c \
	  mandatory/ft_pipe.c \
	  mandatory/cmd_not_found_msg.c \
	  mandatory/file_open_failure_msg.c \
	  mandatory/invalid_number_of_argument_msg.c \
	  mandatory/nsfod_msg.c \
	  mandatory/permission_denied_msg.c \
	  mandatory/s_full_blanks.c \

BNAME = pipex_bonus

BSRC = bonus/main_bonus.c \
	   bonus/pipex_bonus.c \
	   bonus/new_ppx_bonus.c \
	   bonus/initialize_ppx_bonus.c \
	   bonus/ntcharss_copy_bonus.c \
	   bonus/get_size_ntcharss_bonus.c \
	   bonus/ft_strdup_bonus.c \
	   bonus/ft_strlen_bonus.c \
	   bonus/get_path_from_envp_bonus.c \
	   bonus/get_paths_from_path_bonus.c \
	   bonus/ft_split_bonus.c \
	   bonus/free_chars_bonus.c \
	   bonus/ft_substr_bonus.c \
	   bonus/ft_strncmp_bonus.c \
	   bonus/ft_strjoin_bonus.c \
	   bonus/free_ppx_bonus.c \
	   bonus/free_charss_bonus.c \
	   bonus/errormsg_free_exit_bonus.c \
	   bonus/cmd_parsing_bonus.c \
	   bonus/build_slash_and_cmd_bonus.c \
	   bonus/get_ac_av_envp_into_ppx_bonus.c \
	   bonus/free_after_iteration_bonus.c \
	   bonus/set_redirect_bonus.c \
	   bonus/ft_close_bonus.c \
	   bonus/ft_duptwo_bonus.c \
	   bonus/get_next_line.c \
	   bonus/get_next_line_utils.c \
	   bonus/ft_pipe_bonus.c \
	   bonus/ft_fork_bonus.c \
	   bonus/ft_execve_bonus.c \
	   bonus/here_doc_mode.c \
	   bonus/ft_strcmp_bonus.c \
	   bonus/permission_denied_msg_bonus.c \
	   bonus/nsfod_msg_bonus.c \
	   bonus/invalid_number_of_argument_msg_bonus.c \
	   bonus/file_open_failure_msg_bonus.c \
	   bonus/cmd_not_found_msg_bonus.c \
	   bonus/s_full_blanks_bonus.c \
	   bonus/feed_ppx_with_acavenvp_bonus.c \

OBJ = $(SRC:.c=.o)

BOBJ = $(BSRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror
#-g3 -fsanitize=address

all : $(NAME)

mandatory : $(NAME)

bonus :
	@make $(BNAME)

$(NAME): $(OBJ)
	@echo
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 
	@echo project compiled

$(BNAME): $(BOBJ)
	@echo
	@$(CC) $(CFLAGS) $(BOBJ) -o $(BNAME)
	@echo bonus compiled

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "compiling : $<                                      \r"

clean :
	@rm -rf $(OBJ) $(BOBJ)
	@echo object files removed

fclean : clean
	@rm -rf $(NAME) $(BNAME)
	@echo executable removed

re : fclean all

.PHONY:	all mandatory clean fclean re bonus
