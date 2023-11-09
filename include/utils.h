/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:53:09 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/08 19:20:59 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	reset_counts(int *x, int *y);
char	**malloc_full_null_charss(int size);

//before prompt_loop
void	generate_msh_env(t_msh *msh);
void	show_no_args_for_minishell_error_msg(void);
void	build_user_for_prompt(t_msh *msh);
t_msh	*new_msh(void);

#endif
