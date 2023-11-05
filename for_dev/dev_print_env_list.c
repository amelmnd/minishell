/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_print_env_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:39:51 by amennad           #+#    #+#             */
/*   Updated: 2023/11/05 12:14:58 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_list(t_env_list *list)
{
	if (list == NULL)
	{
		pink();
		dprintf(2, "list is empty\n");
		reset();
		return ;
	}
	else
	{
		while (list != NULL)
		{
			green();
			dprintf(2, "name -> [%s]\n", list->name);
			blue();
			dprintf(2, "value -> [%s]\n", list->value);
			list = list->next;
		}
		reset();
	}
}

void	print_debug_env_list(t_env_list *list, char *name)
{
	red();
	dprintf(2, "\n______ %s ______\n", name);
	print_env_list(list);
	red();
	dprintf(2, "***********\n");
	reset();
}
