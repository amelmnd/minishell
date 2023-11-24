/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:25:33 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/24 08:22:08 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redir_array(t_exec_list *exec_list_node)
{
	int	i;

	i = -1;
	if (exec_list_node->redir_array)
	{
		while (++i < exec_list_node->nb_redirects)
			free_chars(&(exec_list_node->redir_array->str));
		free(exec_list_node->redir_array);
		exec_list_node->redir_array = NULL;
	}
}

static void	free_hd(t_exec_list *exec_list_node)
{
	t_hd	*current;
	t_hd	*next;

	if (exec_list_node->hd)
	{
		current = exec_list_node->hd;
		while (current)
		{
			next = current->next;
			free_chars(&(current->str));
			free(current);
			current = next;
		}
		exec_list_node->hd = NULL;
	}
}

void	free_exec_list(t_msh *msh)
{
	t_exec_list	*current;
	t_exec_list	*next;

	if (msh && msh->exec_list)
	{
		current = msh->exec_list;
		while (current)
		{
			next = current->next;
			free_redir_array(current);
			free_chars(&(current->cmd));
			free_ntcharss(&(current->args_array));
			free_hd(current);
			free(current);
			current = next;
		}
		msh->exec_list = NULL;
	}
}
