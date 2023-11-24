/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_list_manage.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:18:22 by amennad           #+#    #+#             */
/*   Updated: 2023/11/24 15:50:29 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expander_list_is_empty(t_exp_list *list)
{
	t_exp_list	*exp_list;

	exp_list = list;
	if (exp_list == NULL)
		return (TRUE);
	return (FALSE);
}

void	init_expander_node(t_exp_list *node)
{
	node->previous = NULL;
	node->next = NULL;
	node->str = NULL;
	node->exp_type = 0;
}

void	expander_push_new_node(t_msh *msh, t_exp_list *new_node)
{
	t_exp_list	*tmp;

	tmp = msh->exp_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->previous = tmp;
}

void	expander_push(t_msh *msh, char *str, t_exp_type type)
{
	t_exp_list	*new_node;

	new_node = (t_exp_list *)malloc(sizeof(t_exp_list));
	init_expander_node(new_node);
	new_node->exp_type = type;
	new_node->str = str;
	if (expander_list_is_empty(msh->exp_list) == TRUE)
		msh->exp_list = new_node;
	else
		expander_push_new_node(msh, new_node);
}
