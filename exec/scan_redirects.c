/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:43:53 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/07 18:44:17 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_redir_in_exec_list_node(t_exec_list *exec_list_node)
{
	int	i;

	if (exec_list_node
		&& exec_list_node->args_array
		&& exec_list_node->redirect_array)
	{
		i = -1;
		while (++i < exec_list_node->nb_redirects
			&& (exec_list_node->contains_write_redirect == FALSE
				|| exec_list_node->contains_read_redirect == FALSE))
		{
			if (exec_list_node->redirect_array[i].exp_type == W_DEST_REDIRECT
				|| exec_list_node->redirect_array[i].exp_type == WA_DEST_REDIRECT)
				exec_list_node->contains_write_redirect = TRUE;
			if (exec_list_node->redirect_array[i].exp_type == R_ORIGIN_REDIRECT
				|| exec_list_node->redirect_array[i].exp_type == LIMITER_HEREDOC)
				exec_list_node->contains_read_redirect = TRUE;
		}
	}
}

void	scan_redirects(t_msh *msh)
{
	t_exec_list	*exec_list_node;

	if (msh && msh->exec_list)
	{
		exec_list_node = msh->exec_list;
		while (exec_list_node)
		{
			check_redir_in_exec_list_node(exec_list_node);
			exec_list_node = exec_list_node->next;
		}
	}
}
