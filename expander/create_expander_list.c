/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_expander_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:15:34 by amennad           #+#    #+#             */
/*   Updated: 2023/11/25 18:55:30 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	defined_type(t_msh *msh, t_lexer_list *tmp)
{
	if (tmp && tmp->lexer_type == PIPE)
		msh->exp_current_type = WORD_EXPANDED;
	else if (tmp && tmp->lexer_type == R_REDIRECT)
		msh->exp_current_type = R_ORIGIN_REDIRECT;
	else if (tmp && tmp->lexer_type == HEREDOC)
		msh->exp_current_type = LIMITER_HEREDOC;
	else if (tmp && tmp->lexer_type == W_REDIRECT)
		msh->exp_current_type = W_DEST_REDIRECT;
	else if (tmp && tmp->lexer_type == W_APPEND_REDIRECT)
		msh->exp_current_type = WA_DEST_REDIRECT;
}

t_lexer_list	*check_lexer_list(t_msh *msh, t_lexer_list *tmp)
{
	defined_type(msh, tmp);
	tmp = generate_str(msh, tmp);
	return (tmp);
}

void	create_expander_list(t_msh *msh)
{
	t_lexer_list	*tmp;

	tmp = msh->lexer_list;
	while (tmp)
	{
		tmp = check_lexer_list(msh, tmp);
		tmp = tmp->next;
	}
}
