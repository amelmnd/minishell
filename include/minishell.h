/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:08:26 by amennad           #+#    #+#             */
/*   Updated: 2023/11/03 13:22:41 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "all_struct.h"
# include "fn_dev.h" // à supprimer à terme
// TODO DELETE START
# include "for_dev.h"
// TODO DELETE END

# include "lexer.h"
# include "parser.h"
# include "expander.h"

# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// IMP : readline.h is last include to avoid errors
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>


void	exit_new_line(void);
void	clean_msh_list(t_msh *msh);
int		ft_msh_strchr(const char *s, int c);

// error
void	exit_synthax_error(char *str);
void	exit_command_not_foud(char *str);

// env
/*
anciennes fonctions d'Amel pour générer l'env_list
int		env_list_is_empty(t_env_list *list);
void	env_first_node(t_env_list *node);
void	env_push_new_node(t_msh *msh, t_env_list *new_node);
void	env_push(t_msh *msh, char *envp);
*/
void	env_list_generate(t_msh *msh, char *envp[]);
char	*ft_getenv(t_msh *msh, char *env_var);
void	split_env_value(char *env_var, char **name, char **value);

#endif
