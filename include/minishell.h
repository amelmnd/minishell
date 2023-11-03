/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:08:26 by amennad           #+#    #+#             */
/*   Updated: 2023/11/03 14:11:11 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "all_struct.h"
// TODO DELETE START
# include "for_dev.h"
// TODO DELETE END

# include "lexer.h"
# include "parser.h"
# include "expander.h"

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// IMP : readline.h is last include to avoid errors
# include <readline/readline.h>

void	exit_new_line(t_msh *msh);
void	clean_msh_list(t_msh *msh);
int		ft_msh_strchr(const char *s, int c);

// error
void	exit_synthax_error(t_msh *msh, char *str);
void	exit_command_not_foud(char *str);

// env
int		env_list_is_empty(t_env_list *list);
void	env_first_node(t_env_list *node);
void	env_push_new_node(t_msh *msh, t_env_list *new_node);
void	env_push(t_msh *msh, char *envp);
void	env_list_generate(t_msh *msh, char *envp[]);
char	*ft_getenv(t_msh *msh, char *env_var);
void	split_env_value(char *env_var, char **name, char **value);

#endif
