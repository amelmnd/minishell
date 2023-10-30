/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:09:30 by amennad           #+#    #+#             */
/*   Updated: 2023/10/30 15:58:07 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO add here other free list inside msh

void	free_lexer_list(t_lexer_list *lexer_list)
{
	t_lexer_list	*current;
	t_lexer_list	*next;

	current = lexer_list;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	free_exp_list(t_exp_list *exp_list)
{
	t_exp_list	*current;
	t_exp_list	*next;

	current = exp_list;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	clean_msh_list(t_msh *msh)
{
	if (msh->lexer_list)
	{
		free_lexer_list(msh->lexer_list);
		msh->lexer_list = NULL;
	}
	if (msh->exp_list)
	{
		free_exp_list(msh->exp_list);
		msh->exp_list = NULL;
		msh->exp_current_type = 0;
	}
}
