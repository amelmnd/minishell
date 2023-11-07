/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:47:47 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/07 18:56:39 by nstoutze         ###   ########.fr       */
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

#endif