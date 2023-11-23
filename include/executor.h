/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:47:47 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 15:50:41 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

//build_exec_list
void	assign_pos_ppl_exec_list(t_msh *msh);
void	build_exec_list(t_msh *msh);
void	feed_exec_list_node(t_msh *msh);
void	feed_exec_list_nodes_cmd(t_msh *msh);
void	feed_exec_list_nodes_data(t_msh *msh);
void	feed_the_only_exec_list_node_data(t_msh *msh);
void	get_nb_pipes_in_exp_list(t_msh *msh);
void	malloc_exec_list_nodes(t_msh *msh);
void	malloc_exec_list_node_arrays(t_msh *msh);
void	scan_redirects(t_msh *msh);

//execution
void	builtin_way(t_msh *msh, t_exec_list *exec_list_node);
void	check_cmd_path_n_exec(t_msh *msh, t_exec_list *exec_list_node);
void	create_pid_t_array(t_msh *msh);
void	do_all_redirections(t_msh *msh, t_exec_list *exec_list_node);
void	do_redir(t_msh *msh, t_exec_list *exec_list_node, int i);
void	execution(t_msh *msh);
void	get_paths_from_path(t_msh *msh);
t_exec	*new_exec(void);
void	wait_and_get_the_last_return_code(t_msh *msh);

// hd
void	feed_append_new_hd_node(t_exec_list *exec_list_node, char *line);
void	create_pipes_for_hd(t_msh *msh);
void	get_all_hd_content(t_msh *msh);
void	get_hd(t_msh *msh, t_exec_list *exec_list_node, int i);
void	get_hd_in_exec_list_node(t_msh *msh, t_exec_list *exec_list_node);
void	mark_all_erased_hd(t_msh *msh);
t_hd	*new_hd(void);
void	retrieve_hd_through_hdpipe(t_exec_list *exec_list_node);
void	send_hd_through_pipe(t_exec_list *exec_list_node);

// builtin_solo_without_fork
void	builtin_solo_without_fork(t_msh *msh);
t_bool	no_fork_solo_builtin(t_msh *msh);
void	do_all_redir_solo_builtin(t_msh *msh);

#endif

