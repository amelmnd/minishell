/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valide_next.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:23:31 by amennad           #+#    #+#             */
/*   Updated: 2023/10/20 15:32:51 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_next(t_msh *msh)
{
	t_lexer_list	*list;
	int				return_code;

	list = msh->lexer_list;
	return_code = 0;
	while (list != NULL)
	{
		printf("type -> [%u]\n", list->lexer_type);
		if (list->lexer_type == PIPE && list->next->lexer_type == BLANK
			&& list->next->next->lexer_type == PIPE)
		{
			exit_synthax_error(msh, "|");
			return (258);
		}
		list = list->next;
	}
	return (return_code);
}
