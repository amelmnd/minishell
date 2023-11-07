/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_exec_list_node_arrays.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:45:43 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/07 17:46:28 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redirect	*malloc_redir_array(int size)
{
	t_redirect	*array;

	array = NULL;
	if (size)
	{
		array = (t_redirect *)malloc(sizeof(t_redirect) * size);
		if (!array)
			return (NULL);
	}
	return (array);
}

static char	**malloc_full_null_charss(int size)
{
	char	**array;
	int		i;

	array = NULL;
	i = -1;
	if (size)
	{
		array = (char **)malloc(sizeof(char *) * (size + 1));
		if (!array)
			return (NULL);
	}
	while (++i < size)
		array[i] = NULL;
	array[size] = NULL;
	return (array);
}

void	malloc_exec_list_node_arrays(t_msh *msh)
{
	t_exec_list	*node;

	if (msh && msh->exec_list)
	{
		node = msh->exec_list;
		while (node)
		{
			if (node->nb_redirects)
				node->redirect_array = malloc_redir_array(node->nb_redirects);
			if (node->nb_words)
				node->args_array = malloc_full_null_charss(node->nb_words);
			node = node->next;
		}
	}
}
