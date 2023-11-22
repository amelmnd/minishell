/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_expander_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:15:34 by amennad           #+#    #+#             */
/*   Updated: 2023/11/22 11:47:01 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	defined_type(t_msh *msh, t_lexer_list *tmp)
{
	if (tmp && tmp->lexer_type == PIPE)
		msh->exp_current_type = WORD_EXPANDED;
	else if (tmp->lexer_type == R_REDIRECT)
		msh->exp_current_type = R_ORIGIN_REDIRECT;
	else if (tmp->lexer_type == HEREDOC)
		msh->exp_current_type = LIMITER_HEREDOC;
	else if (tmp->lexer_type == W_REDIRECT)
		msh->exp_current_type = W_DEST_REDIRECT;
	else if (tmp->lexer_type == W_APPEND_REDIRECT)
		msh->exp_current_type = WA_DEST_REDIRECT;
}

t_lexer_list	*check_lexer_list(t_msh *msh, t_lexer_list *tmp)
{
	defined_type(msh, tmp);
	if (tmp && tmp->lexer_type == PIPE)
	{
		expander_push(msh, tmp->str, PIPE_EXPANDED);
	}
	else if (msh->exp_current_type == R_ORIGIN_REDIRECT)
		tmp = generate_str(msh, tmp, R_ORIGIN_REDIRECT);
	else if (msh->exp_current_type == LIMITER_HEREDOC)
		tmp = generate_str(msh, tmp, LIMITER_HEREDOC);
	else if (msh->exp_current_type == W_DEST_REDIRECT)
		tmp = generate_str(msh, tmp, W_DEST_REDIRECT);
	else if (msh->exp_current_type == WA_DEST_REDIRECT)
		tmp = generate_str(msh, tmp, WA_DEST_REDIRECT);
	else if (msh->exp_current_type == WORD_EXPANDED)
		tmp = generate_str(msh, tmp, WORD_EXPANDED);
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
