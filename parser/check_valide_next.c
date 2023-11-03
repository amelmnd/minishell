/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valide_next.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:23:31 by amennad           #+#    #+#             */
/*   Updated: 2023/11/03 15:08:40 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_next_valide(t_msh *msh, t_lexer_list *list)
{
	(void)msh;
	(void)list;

	if ( list->next == NULL)
		exit_synthax_error(msh, list->str);
	else if ( list->next == NULL
		|| list->next->lexer_type == R_REDIRECT
		|| list->next->lexer_type == HEREDOC
		|| list->next->lexer_type == W_REDIRECT
		|| list->next->lexer_type == W_APPEND_REDIRECT)
		exit_synthax_error(msh, list->next->str);
	else if ((list->next->lexer_type == BLANK
			&& (list->next->next->lexer_type == R_REDIRECT
				|| list->next->next->lexer_type == HEREDOC
				|| list->next->next->lexer_type == W_REDIRECT
				|| list->next->next->lexer_type == W_APPEND_REDIRECT)))
		exit_synthax_error(msh, list->next->next->str);
	else
		return (0);
	return (2);
}

int	check_valid_next(t_msh *msh)
{
	t_lexer_list	*list;
	int				return_code;
	list = msh->lexer_list;
	return_code = 0;
	while (list != NULL)
	{
		if (list->lexer_type == PIPE && list->next->lexer_type == BLANK && list->next->next->lexer_type == PIPE)
		{
			exit_synthax_error(msh, "|");
			return (2);
		}
		else if (list->lexer_type == R_REDIRECT
			|| list->lexer_type == HEREDOC
			||list->lexer_type == W_REDIRECT
			|| list->lexer_type == W_APPEND_REDIRECT)
		{
			return_code = redirect_next_valide(msh, list);
			if (return_code == 2)
				break ;
		}
		list = list->next;
	}
	return (return_code);
}
