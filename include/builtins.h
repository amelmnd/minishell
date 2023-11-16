/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:47:47 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/16 13:31:27 by nstoutze         ###   ########.fr       */
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
void	export_without_args(t_msh *msh);
char	**get_sorted_var_names_array(t_msh *msh);
char	*export_get_var_name(char *arg);
t_bool	is_a_valid_identifier(char *var_name);
void	add_new_couple_name_value(t_msh *msh, char *var_name, char *arg);
void	update_variable(t_msh *msh, char *var_name, char *arg);
char	*export_get_var_value(char *var_name, char *arg);
void	add_var_to_env_list(t_msh *msh, char *var_name, char *arg);
void	export_with_args(t_msh *msh, t_exec_list *exec_list_node);

// unset
void	unset_builtin(t_msh *msh, t_exec_list *exec_list_node);
void	remove_from_env_list(t_msh *msh, char *var_name);

// env
void	env_builtin(t_msh *msh, t_exec_list *exec_list_node);

// exit
void	exit_builtin(t_msh *msh, t_exec_list *exec_list_node);


#endif