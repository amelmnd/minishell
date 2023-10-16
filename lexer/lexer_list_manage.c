/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_manage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:40:04 by amennad           #+#    #+#             */
/*   Updated: 2023/10/16 19:09:10 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_is_empty(t_lexer_list *list)
{
	if (list == NULL)
		return (TRUE);
	return (FALSE);
}



void ft_first_node(t_lexer_list *node)
{
	printf("\nIF list == NULL =>list is empty\n");
	node->previous = NULL;
	node->next = NULL;
}

void	ft_push_new_node(t_lexer_list *list, t_lexer_list	*new_node)
{
	t_lexer_list *tmp;

		printf("\nELSE list == NULL => list is not empty\n");
	tmp = list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->previous = tmp;
}


t_lexer_list	*ft_push(t_lexer_list *list, char *item, t_lexer_type type)
{
	t_lexer_list	*new_node;

	new_node = (t_lexer_list *)malloc(sizeof(t_lexer_list));
	//TODO DEBUG
	print_debug_list(list, "LIST start");
	//TODO END DEBUG
	new_node->lexer_type = 	type;
	new_node->str = item;
	if (list_is_empty(list) == TRUE)
	{
		ft_first_node(new_node);
	}
	else
	{
		ft_push_new_node(list, new_node);
	}
	//TODO DEBUG
	print_debug_list(new_node, "NEW NODE end");
	print_debug_list(list, "LIST end");
	//TODO END DEBUG
	return (new_node);
}
