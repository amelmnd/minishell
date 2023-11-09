/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:47:47 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/08 07:50:43 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

//build_exec_list
void	malloc_exec_list_node_arrays(t_msh *msh);
void	feed_the_only_exec_list_node_data(t_msh *msh);
void	get_nb_pipes_in_exp_list(t_msh *msh);
void	feed_exec_list_nodes_cmd(t_msh *msh);
void	feed_exec_list_nodes_data(t_msh *msh);
void	malloc_exec_list_nodes(t_msh *msh);
void	scan_redirects(t_msh *msh);
void	assign_pos_ppl_exec_list(t_msh *msh);
void	feed_exec_list_node(t_msh *msh);
void	build_exec_list(t_msh *msh);

//exec
// hd
void	mark_all_erased_hd(t_msh *msh);
t_hd	*new_hd(void);
void	get_hd(t_exec_list *exec_list_node, int i);
void	get_hd_in_exec_list_node(t_exec_list *exec_list_node);
void	get_all_hd_content(t_msh *msh);
void	feed_append_new_hd_node(t_exec_list *exec_list_node, char *line);
// hd_pipe
void	create_pipes_for_hd(t_msh *msh);
void	retrieve_hd_through_hdpipe(t_exec_list *exec_list_node, int j);
void	send_hd_through_pipe(t_exec_list *exec_list_node, int j);

t_exec	*new_exec(void);

#endif