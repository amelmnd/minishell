/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit_is_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:51:14 by amennad           #+#    #+#             */
/*   Updated: 2023/10/23 15:17:26 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_start(t_msh *msh)
{
	exit_synthax_error(msh, "|");
	return (258);
}

int	check_end(t_msh *msh, t_lexer_list *list)
{
	if (list->lexer_type == PIPE)
	{
		exit_synthax_error(msh, "|");
		return (258);
	}
	else if (list->lexer_type >= 4 && list->lexer_type <= 7)
	{
		exit_synthax_error(msh, "newline");
		return (258);
	}
	return (0);
}

int	limit_is_valid(t_msh *msh)
{
	t_lexer_list	*list;
	int				return_code;

	list = msh->lexer_list;
	return_code = 0;
	while (list != NULL)
	{
		if (list->previous == NULL && list->lexer_type == PIPE)
			return_code = check_start(msh);
		if (list->next == NULL)
			return_code = check_end(msh, list);
		if (return_code != 0)
			break ;
		list = list->next;
	}
	return (return_code);
}
