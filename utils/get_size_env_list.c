/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_env_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:39:47 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 09:40:05 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size_env_list(t_msh *msh)
{
	int			size;
	t_env_list	*env_list_node;

	size = 0;
	if (msh && msh->env_list)
	{
		env_list_node = msh->env_list;
		while (env_list_node)
		{
			size++;
			env_list_node = env_list_node->next;
		}
	}
	return (size);
}
