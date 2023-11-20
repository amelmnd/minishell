/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:08:26 by amennad           #+#    #+#             */
/*   Updated: 2023/11/20 19:06:36 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 1024

# include "libft/libft.h"
# include "all_struct.h"
// TODO DELETE START
# include "fn_dev.h" // à supprimer à terme
# include "for_dev.h"
// TODO DELETE END

# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "utils.h"
# include "builtins.h"

# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>

// IMP : readline.h is last include to avoid errors
# include <readline/readline.h>
# include <readline/history.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

void	exit_new_line(t_msh *msh);
void	clean_msh_list(t_msh *msh);
int		ft_msh_strchr(const char *s, int c);

// error
void	exit_synthax_error(t_msh *msh, char *str);
void	exit_command_not_foud(char *str);

// env
void	env_list_generate(t_msh *msh, char *envp[]);
char	*ft_getenv(t_msh *msh, char *env_var);
void	split_env_value(char *env_var, char **name, char **value);

// signal
void	ft_signal(t_msh *msh);
void	sig_handler(int sig);

#endif
