/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_send_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:29:03 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/18 21:29:13 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes_for_hd(t_msh *msh)
{
	int			ret;
	t_exec_list	*exec_list_node;

	if (msh && msh->exec_list)
	{
		exec_list_node = msh->exec_list;
		while (exec_list_node)
		{
			if (exec_list_node->contains_hd == TRUE)
				ret = pipe(exec_list_node->hd_send_pipe);
			exec_list_node = exec_list_node->next;
		}
	}
}

void	retrieve_hd_through_hdpipe(t_exec_list *exec_list_node)
{
	int	ret;

	if (exec_list_node)
	{
		close(exec_list_node->hd_send_pipe[WRITE]);
		ret = dup2(exec_list_node->hd_send_pipe[READ], STDIN_FILENO);
		close(exec_list_node->hd_send_pipe[READ]);
	}
}

static void	write_hd_in_the_pipe(t_exec_list *exec_list_node)
{
	t_hd	*hd_node;

	if (exec_list_node && exec_list_node->hd)
	{
		hd_node = exec_list_node->hd;
		while (hd_node)
		{
			if (!(hd_node->str))
				write(exec_list_node->hd_send_pipe[WRITE], "\n", 1);
			else
			{
				write(exec_list_node->hd_send_pipe[WRITE],
					hd_node->str, ft_strlen(hd_node->str));
			}
			hd_node = hd_node->next;
		}
	}
}

void	send_hd_through_pipe(t_exec_list *exec_list_node)
{
	if (exec_list_node && exec_list_node->contains_hd)
	{
		write_hd_in_the_pipe(exec_list_node);
		close(exec_list_node->hd_send_pipe[READ]);
		close(exec_list_node->hd_send_pipe[WRITE]);
	}
}
