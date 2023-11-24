/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:17:44 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/24 17:29:52 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer_list(t_msh *msh)
{
	t_lexer_list	*current;
	t_lexer_list	*next;

	if (msh->lexer_list)
	{
		current = msh->lexer_list;
		while (current != NULL)
		{
			next = current->next;
			free_chars(&(current->str));
			free(current);
			current = next;
		}
		msh->lexer_list = NULL;
	}
}
