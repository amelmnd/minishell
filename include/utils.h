/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:53:09 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/14 00:55:47 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	reset_counts(int *x, int *y);
char	**malloc_full_null_charss(int size);

//before prompt_loop
void		generate_msh_env(t_msh *msh);
void		show_no_args_for_minishell_error_msg(void);
void		build_user_for_prompt(t_msh *msh);
t_msh		*new_msh(void);
t_env_list	*new_env_list(void);
void		ft_execve(t_msh *msh, t_exec_list *exec_list_node);
void		free_ints(int **dust);
char		*msh_getenv(t_msh *msh, char *var_name);

#endif
