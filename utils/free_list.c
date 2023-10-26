/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:09:30 by amennad           #+#    #+#             */
/*   Updated: 2023/10/26 09:39:55 by amennad          ###   ########.fr       */
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

void	clean_msh_list(t_msh *msh)
{
	if (msh->lexer_list)
	{
		free_lexer_list(msh->lexer_list);
		msh->lexer_list = NULL;
	}
}
