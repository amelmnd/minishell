/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_print_exp_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:39:51 by amennad           #+#    #+#             */
/*   Updated: 2023/11/03 13:41:43 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void    print_exp_type_one_line(int exp_type)
{
	switch (exp_type)
	{
		case 0:
			printf("type -> WORD_EXPANDED");
			break;
		case 1:
			printf("type -> R_ORIGIN_REDIRECT");
			break;
		case 2:
			printf("type -> LIMITER_HEREDOC");
			break;
		case 3:
			printf("type -> W_DEST_REDIRECT");
			break;
		case 4:
			printf("type -> WA_DEST_REDIRECT");
			break;
		case 5:
			printf("type -> PIPE_EXPANDED");
			break;
		default:
			break;
	}
	printf("\n");
}
*/

void	print_exp_list(t_exp_list *list)
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
			if (list->str)
			{
				green();
				printf("str -> [%s]\n", list->str);
			}
			else if (list->str)
			{
				blue();
				printf("v_name -> [%s]\n", list->str);
			}
			cyan();
			//print_exp_type_one_line(list->exp_type);
			list = list->next;
		}
		reset();
	}
}

void	print_debug_exp_list(t_exp_list *list, char *name)
{
	red();
	printf("\n______ %s ______\n", name);
	print_exp_list(list);
	red();
	printf("***********\n");
	reset();
}
