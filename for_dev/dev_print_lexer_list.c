/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_print_lexer_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:39:51 by amennad           #+#    #+#             */
/*   Updated: 2023/11/03 14:35:54 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_lexer_type_one_line(int lexer_type)
{
	switch (lexer_type)
	{
		case 0:
			printf("type -> PIPE");
			break;
		case 1:
			printf("type -> WORD");
			break;
		case 2:
			printf("type -> S_QUOTE");
			break;
		case 3:
			printf("type -> D_QUOTE");
			break;
		case 4:
			printf("type -> SPECIAL_VAR");
			break;
		case 5:
			printf("type -> R_REDIRECT");
			break;
		case 6:
			printf("type -> HEREDOC");
			break;
		case 7:
			printf("type -> W_REDIRECT");
			break;
		case 8:
			printf("type -> W_APPEND_REDIRECT");
			break;
		case 9:
			printf("type -> BLANK");
			break;
		case 10:
			printf("type -> VARIABLE");
			break;
		case 11:
			printf("type -> RETURN_VALUE");
			break;
		case 12:
			printf("type -> D_QUOTE_VAR");
			break;
		default:
			break;
	}

}

void	print_lexer_list(t_lexer_list *list)
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
				printf("str -> [%s]	", list->str);
			}
			cyan();
			print_lexer_type_one_line(list->lexer_type);
			if (list->var_name)
			{
				blue();
				printf("var_name -> [%s]	", list->var_name);
				printf("var_value -> [%s]	", list->var_value);
			}
			printf("\n");
			list = list->next;
		}
		reset();
	}
}

void	print_debug_lexer_list(t_lexer_list *list, char *name)
{
	red();
	printf("\n______ %s ______\n", name);
	print_lexer_list(list);
	red();
	printf("***********\n");
	reset();
}
