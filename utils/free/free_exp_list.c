/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exp_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:19:21 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/24 17:30:09 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exp_list(t_msh *msh)
{
	t_exp_list	*current;
	t_exp_list	*next;

	if (msh->exp_list)
	{
		current = msh->exp_list;
		while (current != NULL)
		{
			next = current->next;
			free(current);
			current = next;
		}
		msh->exp_list = NULL;
		msh->exp_current_type = 0;
	}
}
