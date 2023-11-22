/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:53:09 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/22 11:04:42 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void		reset_counts(int *x, int *y);
char		**malloc_full_null_charss(int size);

//before prompt_loop
void		generate_msh_env(t_msh *msh);
void		show_no_args_for_minishell_error_msg(void);
void		build_user_for_prompt(t_msh *msh);
t_msh		*new_msh(void);
t_env_list	*new_env_list(void);
void		ft_execve(t_msh *msh, t_exec_list *exec_list_node);
void		free_ints(int **dust);
char		*msh_getenv(t_msh *msh, char *var_name);
int			get_size_env_list(t_msh *msh);
int			is_chr_in_str(char *s, char c);
void		free_chars(char **dust);

void	free_lexer_list(t_lexer_list *list);
void	free_exp_list(t_msh *msh);
void	free_exec_list(t_msh *msh);
void	free_exec(t_msh *msh);
void	free_msh(t_msh *msh);

void	errmsg_free_exit(t_msh *msh, char *msg);

#endif
