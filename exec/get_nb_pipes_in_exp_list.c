/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_pipes_in_exp_list.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:24:20 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/07 18:24:29 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_nb_pipes_in_exp_list(t_msh *msh)
{
	int			nb_pipes;
	t_exp_list	*exp_list_node;

	nb_pipes = 0;
	if (msh && msh->exp_list)
	{
		exp_list_node = msh->exp_list;
		while (exp_list_node)
		{
			if (exp_list_node->exp_type == PIPE_EXPANDED)
				nb_pipes++;
			exp_list_node = exp_list_node->next;
		}
		msh->exec_list->nb_pipes = nb_pipes;
	}
}
