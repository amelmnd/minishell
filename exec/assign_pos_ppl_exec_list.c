/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_pos_ppl_exec_list.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:45:55 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/07 18:46:24 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pos_ppl(t_msh *msh, t_exec_list *exec_list_node, int i)
{
	if (msh && msh->exec_list)
	{
		if (!i)
			exec_list_node->pos_ppl = FIRST;
		else if (i == exec_list_node->nb_pipes)
			exec_list_node->pos_ppl = LAST;
		else
			exec_list_node->pos_ppl = MIDDLE;
	}
}

void	assign_pos_ppl_exec_list(t_msh *msh)
{
	t_exec_list	*exec_list_node;
	int			i;

	if (msh && msh->exec_list)
	{
		exec_list_node = msh->exec_list;
		if (!(exec_list_node->nb_pipes))
		{
			exec_list_node->pos_ppl = SOLO;
			return ;
		}
		i = 0;
		while (exec_list_node)
		{
			set_pos_ppl(msh, exec_list_node, i);
			i++;
			exec_list_node = exec_list_node->next;
		}
	}
}
