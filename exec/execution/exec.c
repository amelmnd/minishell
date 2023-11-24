/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:01:27 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/24 07:58:52 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// builtin_way contains an exit, which runs in case of builtin
// check_cmd_path_n_exec contains an exit, which runs anyway
static void	child_part(t_msh *msh, t_exec_list *exec_list_node)
{
	if (!(msh->exec->child))
	{
		do_all_redirections(msh, exec_list_node);
		if (exec_list_node->cmd)
		{
			builtin_way(msh, exec_list_node);
			check_cmd_path_n_exec(msh, exec_list_node);
		}
		else
			exit(EXIT_SUCCESS);
	}
}

static void	parent_part(t_msh *msh, t_exec_list *exec_list_node, int j)
{
	msh->exec->pid_t_array[j] = msh->exec->child;
	if (exec_list_node->pos_ppl == SOLO || exec_list_node->pos_ppl == LAST)
		msh->exec->last_child = msh->exec->child;
	send_hd_through_pipe(exec_list_node);
	if (exec_list_node->pos_ppl == MIDDLE || exec_list_node->pos_ppl == LAST)
		close(msh->exec->fd_temp);
	if (exec_list_node->pos_ppl == FIRST || exec_list_node->pos_ppl == MIDDLE)
		msh->exec->fd_temp = dup(msh->exec->pipefd[READ]);
	if (exec_list_node->pos_ppl != SOLO)
	{
		close(msh->exec->pipefd[READ]);
		close(msh->exec->pipefd[WRITE]);
	}
}

// child_part exits anyway
void	exec_loop(t_msh *msh)
{
	t_exec_list	*exec_list_node;
	int			j;

	exec_list_node = msh->exec_list;
	j = 0;
	while (exec_list_node)
	{
		if (exec_list_node->pos_ppl != SOLO)
		{
			if (pipe(msh->exec->pipefd) < 0)
				errmsg_free_exit(msh, "pipe");
		}
		msh->exec->child = fork();
		if (msh->exec->child < 0)
			errmsg_free_exit(msh, "fork");
		child_part(msh, exec_list_node);
		parent_part(msh, exec_list_node, j);
		exec_list_node = exec_list_node->next;
		j++;
	}
}

void	execution(t_msh *msh)
{
	msh->exec = new_exec();
	get_all_hd_content(msh);
	mark_all_erased_hd(msh);
	get_paths_from_path(msh);
	if (no_fork_solo_builtin(msh))
		builtin_solo_without_fork(msh);
	else
	{
		create_pipes_for_hd(msh);
		create_pid_t_array(msh);
		exec_loop(msh);
		if (msh->exec_list->nb_pipes)
			close(msh->exec->fd_temp);
		wait_and_get_the_last_return_code(msh);
	}
	if (msh->exec_list->nb_pipes)
		close(msh->exec->fd_temp);
}
/*
	//Peut-être mettre des close finaux;
	//Ou peut-être que les close dans l'execloop suffisent;
	// vérifier avec lsof
*/