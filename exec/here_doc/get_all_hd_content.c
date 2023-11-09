/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_hd_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:24:11 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/08 08:11:44 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	hd_in_exec_list_node(t_exec_list *exec_list_node)
{
	int		i;

	i = -1;
	if (exec_list_node && exec_list_node->redirect_array)
	{
		while (++i < exec_list_node->nb_redirects)
		{
			if (exec_list_node->redirect_array[i].exp_type == LIMITER_HEREDOC)
				return (TRUE);
		}
	}
	return (FALSE);
}

void	get_all_hd_content(t_msh *msh)
{
	t_exec_list	*exec_list_node;

	if (msh && msh->exec_list)
	{
		exec_list_node = msh->exec_list;
		while (exec_list_node)
		{
			if (hd_in_exec_list_node(exec_list_node))
			{
				exec_list_node->hd = new_hd();
				exec_list_node->contains_hd = TRUE;
				get_hd_in_exec_list_node(exec_list_node);
			}
			exec_list_node = exec_list_node->next;
		}
	}
}
