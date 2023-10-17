/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_manage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:40:04 by amennad           #+#    #+#             */
/*   Updated: 2023/10/17 17:41:24 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_list_is_empty(t_lexer_list *list)
{
	if (list == NULL)
		return (TRUE);
	return (FALSE);
}

void	lexer_first_node(t_lexer_list *node)
{
	node->previous = NULL;
	node->next = NULL;
}

void	lexer_push_new_node(t_msh *msh, t_lexer_list	*new_node)
{
	t_lexer_list	*tmp;

	tmp = msh->lexer_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->previous = tmp;
}

void	lexer_push(t_msh *msh, char *str, t_lexer_type type)
{
	t_lexer_list	*new_node;

	new_node = (t_lexer_list *)malloc(sizeof(t_lexer_list));
	new_node->lexer_type = type;
	new_node->str = str;
	if (lexer_list_is_empty(msh->lexer_list) == TRUE)
	{
		lexer_first_node(new_node);
		msh->lexer_list = new_node;
	}
	else
	{
		lexer_push_new_node(msh, new_node);
	}
}
