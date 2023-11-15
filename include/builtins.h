/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:47:47 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/14 20:09:58 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// builtin_solo_without_fork
void	builtin_solo_without_fork(t_msh *msh);
t_bool	no_fork_solo_builtin(t_msh *msh);

// echo
void	echo_builtin(t_msh *msh, t_exec_list *exec_list_node);

// cd
void	cd_builtin(t_msh *msh, t_exec_list *exec_list_node);

// pwd
void	pwd_builtin(t_msh *msh, t_exec_list *exec_list_node);

// export
void	export_builtin(t_msh *msh, t_exec_list *exec_list_node);

// unset
void	unset_builtin(t_msh *msh, t_exec_list *exec_list_node);

// env
void	env_builtin(t_msh *msh, t_exec_list *exec_list_node);

// exit
void	exit_builtin(t_msh *msh, t_exec_list *exec_list_node);


#endif