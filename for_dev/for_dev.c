/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_dev.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:39:51 by amennad           #+#    #+#             */
/*   Updated: 2023/10/16 15:08:24 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_list(t_lexer_list *list)
{
	if (list == NULL)
	{
		printf("list is empty\n");
		return;
	}
	else
	{
		while (list != NULL)
		{
			if (list->str)
				printf("str -> [%s]\n", list->str);
			else if (list->var_name)
				printf("v_name -> [%s]\n", list->var_name);
			printf("type -> [%u]\n", list->lexer_type);
			list = list->next;
		}
	}
}

void print_debug_list(t_lexer_list *list, char *name)
{
	printf("\n______ %s ______\n", name);
	print_list(list);
	printf("***********\n");
}