/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_manage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:40:04 by amennad           #+#    #+#             */
/*   Updated: 2023/11/02 18:22:04 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_list_is_empty(t_msh *msh)
{
	t_lexer_list	*lexer_list;

	lexer_list = msh->lexer_list;
	if (lexer_list == NULL)
		return (TRUE);
	return (FALSE);
}

void	init_lexer_node(t_lexer_list *node)
{
	node->previous = NULL;
	node->next = NULL;
	node->str = NULL;
	node->var_name = NULL;
	node->var_value = NULL;
	node->lexer_type = 0;
}

void	lexer_push_new_node(t_msh *msh, t_lexer_list *new_node)
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
	init_lexer_node(new_node);
	new_node->lexer_type = type;
	new_node->str = ft_strdup(str);
	if (lexer_list_is_empty(msh) == TRUE)
		msh->lexer_list = new_node;
	else
		lexer_push_new_node(msh, new_node);
}
