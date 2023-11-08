/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_all_erased_hd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:34:39 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/07 22:37:59 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mark_erased_hd(t_exec_list *exec_list_node)
{
	int	i;
	int	nb_hd;

	if (exec_list_node && exec_list_node->redirect_array)
	{
		i = exec_list_node->nb_redirects;
		nb_hd = 0;
		while (--i >= 0)
		{
			if (exec_list_node->redirect_array[i].exp_type == LIMITER_HEREDOC)
			{
				nb_hd++;
				if (nb_hd >= 2)
					exec_list_node->redirect_array[i].exp_type = HEREDOC_ERASED;
			}
		}
	}
}

void	mark_all_erased_hd(t_msh *msh)
{
	t_exec_list	*exec_list_node;

	if (msh && msh->exec_list)
	{
		exec_list_node = msh->exec_list;
		while (exec_list_node)
		{
			mark_erased_hd(exec_list_node);
			exec_list_node = exec_list_node->next;
		}
	}
}
