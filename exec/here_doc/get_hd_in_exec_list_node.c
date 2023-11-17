/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hd_in_exec_list_node.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:21:53 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/16 23:40:47 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_hd(t_exec_list *exec_list_node)
{
	t_hd	*hd_node;
	t_hd	*hd_node_next;

	if (exec_list_node && exec_list_node->hd)
	{
		hd_node = exec_list_node->hd;
		hd_node_next = NULL;
		while (hd_node)
		{
			hd_node_next = hd_node->next;
			if (hd_node->str)
			{
				free(hd_node->str);
				hd_node->str = NULL;
			}
			free(hd_node);
			hd_node = hd_node_next;
		}
	}
}

void	get_hd_in_exec_list_node(t_msh *msh, t_exec_list *exec_list_node)
{
	int	i;

	i = -1;
	if (exec_list_node && exec_list_node->redirect_array)
	{
		while (++i < exec_list_node->nb_redirects)
		{
			if (exec_list_node->redirect_array[i].exp_type == LIMITER_HEREDOC)
			{
				if (exec_list_node->hd->str)
				{
					clear_hd(exec_list_node);
					exec_list_node->hd = new_hd();
				}
				get_hd(msh, exec_list_node, i);
			}
		}
		dprintf(2, "get_hd_in_exec_list_node : affichage de la liste chainée heredoc\n");
		print_hd_in_exec_list_node(exec_list_node);
		dprintf(2, "get_hd_in_exec_list_node : fin de l'affichage\n");
	}
}
