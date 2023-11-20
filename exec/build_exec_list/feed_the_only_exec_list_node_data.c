/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feed_the_only_exec_list_node_data.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:21:21 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/07 18:22:54 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	feed_the_only_exec_list_node_data(t_msh *msh)
{
	t_exp_list	*exp_list_node_i;

	if (msh && msh->exp_list && msh->exec_list)
	{
		exp_list_node_i = msh->exp_list;
		while (exp_list_node_i)
		{
			if (exp_list_node_i->exp_type == WORD_EXPANDED)
				msh->exec_list->nb_words++;
			else
				msh->exec_list->nb_redirects++;
			exp_list_node_i = exp_list_node_i->next;
		}
	}
}
