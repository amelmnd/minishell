/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exec_list_del.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:47:41 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/18 21:47:42 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_exec_list(t_msh *msh)
{
	malloc_exec_list_nodes(msh);
	feed_exec_list_nodes_data(msh);
	malloc_exec_list_node_arrays(msh);
	feed_exec_list_nodes_cmd(msh);
	assign_pos_ppl_exec_list(msh);
	feed_exec_list_node(msh);
	scan_redirects(msh);
}
