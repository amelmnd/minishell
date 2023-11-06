/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_print_lexer_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:39:51 by amennad           #+#    #+#             */
/*   Updated: 2023/11/05 12:15:29 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_lexer_type_one_line(int lexer_type)
{
	switch (lexer_type)
	{
		case 0:
			dprintf(2, "type -> PIPE");
			break;
		case 1:
			dprintf(2, "type -> WORD");
			break;
		case 2:
			dprintf(2, "type -> S_QUOTE");
			break;
		case 3:
			dprintf(2, "type -> D_QUOTE");
			break;
		case 4:
			dprintf(2, "type -> SPECIAL_VAR");
			break;
		case 5:
			dprintf(2, "type -> R_REDIRECT");
			break;
		case 6:
			dprintf(2, "type -> HEREDOC");
			break;
		case 7:
			dprintf(2, "type -> W_REDIRECT");
			break;
		case 8:
			dprintf(2, "type -> W_APPEND_REDIRECT");
			break;
		case 9:
			dprintf(2, "type -> BLANK");
			break;
		case 10:
			dprintf(2, "type -> VARIABLE");
			break;
		case 11:
			dprintf(2, "type -> RETURN_VALUE");
			break;
		case 12:
			dprintf(2, "type -> D_QUOTE_VAR");
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
				dprintf(2, "str -> [%s]	", list->str);
			}
			cyan();
			print_lexer_type_one_line(list->lexer_type);
			if (list->var_name)
			{
				blue();
				dprintf(2, "var_name -> [%s]	", list->var_name);
				dprintf(2, "var_value -> [%s]	", list->var_value);
			}
			dprintf(2, "\n");
			list = list->next;
		}
		reset();
	}
}

void	print_debug_lexer_list(t_lexer_list *list, char *name)
{
	red();
	dprintf(2, "\n______ %s ______\n", name);
	print_lexer_list(list);
	red();
	dprintf(2, "***********\n");
	reset();
}
