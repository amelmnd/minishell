/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:04:31 by amennad           #+#    #+#             */
/*   Updated: 2023/10/30 16:00:18 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_list_is_empty(t_env_list *list)
{
	if (list == NULL)
		return (TRUE);
	return (FALSE);
}

void	env_first_node(t_env_list *node)
{
	node->previous = NULL;
	node->next = NULL;
}

void	env_push_new_node(t_msh *msh, t_env_list *new_node)
{
	t_env_list	*tmp;

	tmp = msh->env_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->previous = tmp;
}

void	env_push(t_msh *msh, char *envp)
{
	t_env_list	*new_node;

	new_node = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new_node)
		return ;
	split_env_value(envp, &new_node->name, &new_node->value);
	if (env_list_is_empty(msh->env_list) == TRUE)
	{
		env_first_node(new_node);
		msh->env_list = new_node;
	}
	else
		env_push_new_node(msh, new_node);
}

void	env_list_generate(t_msh *msh, char *envp[])
{
	int		index;

	index = 0;
	while (envp[index])
	{
		env_push(msh, envp[index]);
		index++;
	}
}
