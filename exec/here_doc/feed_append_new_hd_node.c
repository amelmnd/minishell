/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feed_append_new_hd_node.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 07:49:23 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/08 08:09:35 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	feed_append_new_hd_node(t_exec_list *exec_list_node, char *line)
{
	t_hd	*new_hd_node;
	t_hd	*last_hd_node;

	new_hd_node = new_hd();
	if (new_hd_node && exec_list_node)
	{
		new_hd_node->str = ft_strdup(line);
		last_hd_node = exec_list_node->hd;
		while (last_hd_node->next)
			last_hd_node = last_hd_node->next;
		last_hd_node->next = new_hd_node;
	}
}
