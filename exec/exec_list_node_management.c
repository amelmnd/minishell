/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list_node_management.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:42:23 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/19 15:01:57 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_exec_list_node(t_exec_list *exec_list_node)
{
	if (exec_list_node)
	{
		exec_list_node->next = NULL;
		exec_list_node->previous = NULL;
		exec_list_node->redirect_array = NULL;
		exec_list_node->nb_redirects = 0;
		exec_list_node->cmd = NULL;
		exec_list_node->args_array = NULL;
		exec_list_node->nb_words = 0;
		exec_list_node->next_pipe = 0;
		exec_list_node->nb_pipes = 0;
		exec_list_node->hd_send_pipe[READ] = -1;
		exec_list_node->hd_send_pipe[WRITE] = -1;
		exec_list_node->hd_get_pipe[READ] = -1;
		exec_list_node->hd_get_pipe[WRITE] = -1;
		exec_list_node->hd_get_child = -1;
		exec_list_node->contains_hd = FALSE;
		exec_list_node->pos_ppl = INIT_POS_PPL_VALUE;
		exec_list_node->contains_write_redirect = FALSE;
		exec_list_node->contains_read_redirect = FALSE;
		exec_list_node->hd = NULL;
	}
}

static t_exec_list	*new_exec_list_node(void)
{
	t_exec_list	*new;

	new = NULL;
	new = (t_exec_list *)malloc(sizeof(t_exec_list));
	if (!new)
		return (NULL);
	init_exec_list_node(new);
	return (new);
}

static void	plug_exec_list_node(t_msh *msh, t_exec_list *exec_list_node)
{
	t_exec_list	*exec_list_i;

	exec_list_i = msh->exec_list;
	if (msh && exec_list_node)
	{
		while (exec_list_i->next)
			exec_list_i = exec_list_i->next;
		exec_list_i->next = exec_list_node;
		exec_list_node->previous = exec_list_i;
	}
}

static void	create_and_plug_all_empty_exec_list_nodes(t_msh *msh)
{
	int			i;
	int			nb_pipes;
	t_exec_list	*exec_list_node;

	i = -1;
	if (msh && msh->exec_list)
	{
		nb_pipes = msh->exec_list->nb_pipes;
		while (++i < nb_pipes)
		{
			exec_list_node = NULL;
			exec_list_node = new_exec_list_node();
			exec_list_node->nb_pipes = nb_pipes;
			plug_exec_list_node(msh, exec_list_node);
		}
	}
}

void	malloc_exec_list_nodes(t_msh *msh)
{
	if (msh)
	{
		msh->exec_list = new_exec_list_node();
		get_nb_pipes_in_exp_list(msh);
		if (msh->exec_list && msh->exec_list->nb_pipes)
			create_and_plug_all_empty_exec_list_nodes(msh);
	}
}
