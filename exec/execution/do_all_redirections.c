/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_all_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 21:56:31 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/24 23:07:47 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_stdin(t_msh *msh, t_exec_list *exec_list_node)
{
	if (msh && msh->exec && exec_list_node)
	{
		if (exec_list_node->pos_ppl == MIDDLE
			|| exec_list_node->pos_ppl == LAST)
		{
			if (dup2(msh->exec->fd_temp, STDIN_FILENO) < 0)
				errmsg_free_exit(msh, "dup2");
		}
	}
}

static void	manage_stdout(t_msh *msh, t_exec_list *exec_list_node)
{
	if (msh && msh->exec && exec_list_node)
	{
		if ((exec_list_node->pos_ppl == FIRST
				|| exec_list_node->pos_ppl == MIDDLE)
			&& exec_list_node->contains_write_redirect == FALSE)
		{
			if (dup2(msh->exec->pipefd[WRITE], STDOUT_FILENO) < 0)
				errmsg_free_exit(msh, "dup2");
		}
	}
}

void	do_all_redirections(t_msh *msh, t_exec_list *exec_list_node)
{
	int	i;

	if (msh && msh->exec && exec_list_node)
	{
		if (exec_list_node->pos_ppl == MIDDLE || exec_list_node->pos_ppl == FIRST)
			close(msh->exec->pipefd[READ]);
		manage_stdin(msh, exec_list_node);
		if (exec_list_node->contains_hd)
			close(exec_list_node->hd_send_pipe[WRITE]);
		i = -1;
		while (++i < exec_list_node->nb_redirects)
			do_redir(msh, exec_list_node, i);
		manage_stdout(msh, exec_list_node);
		if (exec_list_node->pos_ppl == MIDDLE
			|| exec_list_node->pos_ppl == LAST)
		{
			close(msh->exec->fd_temp);
			close(msh->exec->pipefd[WRITE]);
		}
		if (exec_list_node->contains_read_redirect)
			close(msh->exec->fd_read_redirect);
		if (exec_list_node->contains_write_redirect)
			close(msh->exec->fd_write_redirect);
	}
}
