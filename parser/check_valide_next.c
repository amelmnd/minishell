/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valide_next.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:23:31 by amennad           #+#    #+#             */
/*   Updated: 2023/10/20 19:58:18 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	💯PIPE,❌
	WORD,✅
	S_QUOTE,✅
	D_QUOTE,✅
	R_REDIRECT,❌
	HEREDOC,❌
	W_REDIRECT,❌
	W_APPEND_REDIRECT,❌
	BLANK,💀 check next
	VARIABLE,✅
	RETURN_VALUE,✅
	SPECIAL_VAR ✅
};
		// && list->next->next->lexer_type != WORD
		// && list->next->next->lexer_type != S_QUOTE
		// && list->next->next->lexer_type != D_QUOTE
		// && list->next->next->lexer_type != VARIABLE
		// && list->next->next->lexer_type != RETURN_VALUE
*/
int	redirect_next_valide(t_msh *msh, t_lexer_list *list)
{
	if (list->next->lexer_type == R_REDIRECT
		|| list->next->lexer_type == HEREDOC
		|| list->next->lexer_type == W_REDIRECT
		|| list->next->lexer_type == W_APPEND_REDIRECT)
	{
		exit_synthax_error(msh, list->next->str);
		return (258);
	}
	else if ((list->next->lexer_type == BLANK
			&& (list->next->next->lexer_type == R_REDIRECT
				|| list->next->next->lexer_type == HEREDOC
				|| list->next->next->lexer_type == W_REDIRECT
				|| list->next->next->lexer_type == W_APPEND_REDIRECT)))
	{
		exit_synthax_error(msh, list->next->next->str);
		return (258);
	}
	return (0);
}

int	check_valid_next(t_msh *msh)
{
	t_lexer_list	*list;
	int				return_code;

	list = msh->lexer_list;
	return_code = 0;
	while (list != NULL)
	{
		if (list->lexer_type == PIPE && list->next->lexer_type == BLANK
			&& list->next->next->lexer_type == PIPE)
		{
			exit_synthax_error(msh, "|");
			return (258);
		}
		else if (list->lexer_type == R_REDIRECT
			|| list->lexer_type == HEREDOC
			||list->lexer_type == W_REDIRECT
			|| list->lexer_type == W_APPEND_REDIRECT)
		{
			redirect_next_valide(msh, list);
		}
		list = list->next;
	}
	return (return_code);
}
