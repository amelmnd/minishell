/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_print_exp_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:39:51 by amennad           #+#    #+#             */
/*   Updated: 2023/11/10 15:17:05 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_exp_type_ls(int exp_type)
{
	switch (exp_type)
	{
		case 1:
			dprintf(2, "type -> WORD_EXPANDED");
			break;
		case 2:
			dprintf(2, "type -> R_ORIGIN_REDIRECT");
			break;
		case 3:
			dprintf(2, "type -> LIMITER_HEREDOC");
			break;
		case 4:
			dprintf(2, "type -> W_DEST_REDIRECT");
			break;
		case 5:
			dprintf(2, "type -> WA_DEST_REDIRECT");
			break;
		case 6:
			dprintf(2, "type -> PIPE_EXPANDED");
			break;
		default:
			break;
	}
	dprintf(2, "\n");
}


void	print_exp_list(t_exp_list *list)
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
			if (list->str)
			{
				green();
				dprintf(2, "str -> [%s]\n", list->str);
			}
			cyan();
			print_exp_type_ls(list->exp_type);
			list = list->next;
		}
		reset();
	}
}

void	print_debug_exp_list(t_exp_list *list, char *name)
{
	red();
	dprintf(2, "\n______ %s ______\n", name);
	print_exp_list(list);
	red();
	dprintf(2, "***********\n");
	reset();
}
