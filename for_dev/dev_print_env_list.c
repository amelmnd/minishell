/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_print_env_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:39:51 by amennad           #+#    #+#             */
/*   Updated: 2023/10/25 13:20:50 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_list(t_env_list *list)
{
	if (list == NULL)
	{
		pink();
		printf("list is empty\n");
		reset();
		return ;
	}
	else
	{
		while (list != NULL)
		{
			green();
			printf("name -> [%s]\n", list->name);
			blue();
			printf("value -> [%s]\n", list->value);
			list = list->next;
		}
		reset();
	}
}

void	print_debug_env_list(t_env_list *list, char *name)
{
	red();
	printf("\n______ %s ______\n", name);
	print_env_list(list);
	red();
	printf("***********\n");
	reset();
}
