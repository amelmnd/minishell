/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feed_exec_list_nodes_data.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:26:50 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/07 18:55:24 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	felnd_cheks_and_inits(t_msh *msh, int *nb_w, int *nb_r)
{
	*nb_w = 0;
	*nb_r = 0;
	if (msh && msh->exp_list && msh->exec_list)
		return (TRUE);
	return (FALSE);
}

static void	feed_exec_list_node_data(t_msh *msh)
{
	t_exp_list	*exp_list_node;
	t_exec_list	*exec_list_node;
	int			nb_w;
	int			nb_r;

	if (!felnd_cheks_and_inits(msh, &nb_w, &nb_r))
		return ;
	exp_list_node = msh->exp_list;
	exec_list_node = msh->exec_list;
	while (exp_list_node)
	{
		if (exp_list_node->exp_type == WORD_EXPANDED)
			nb_w++;
		else if (exp_list_node->exp_type != PIPE_EXPANDED)
			nb_r++;
		else
		{
			exec_list_node->nb_words = nb_w;
			exec_list_node->nb_redirects = nb_r;
			exec_list_node = exec_list_node->next;
			reset_counts(&nb_w, &nb_r);
		}
		exp_list_node = exp_list_node->next;
	}
}

static void	feed_last_exec_list_node_data(t_msh *msh)
{
	t_exec_list	*last_exec_list_node;
	t_exp_list	*last_pipe_exp_list_node;

	if (msh && msh->exp_list && msh->exec_list)
	{
		last_exec_list_node = msh->exec_list;
		last_pipe_exp_list_node = msh->exp_list;
		while (last_exec_list_node->next)
			last_exec_list_node = last_exec_list_node->next;
		while (last_pipe_exp_list_node->next)
			last_pipe_exp_list_node = last_pipe_exp_list_node->next;
		while (last_pipe_exp_list_node->exp_type != PIPE_EXPANDED)
		{
			if (last_pipe_exp_list_node->exp_type == WORD_EXPANDED)
				last_exec_list_node->nb_words++;
			else
				last_exec_list_node->nb_redirects++;
			last_pipe_exp_list_node = last_pipe_exp_list_node->previous;
		}
	}
}

void	feed_exec_list_nodes_data(t_msh *msh)
{
	if (msh->exec_list->nb_pipes)
	{
		feed_exec_list_node_data(msh);
		feed_last_exec_list_node_data(msh);
	}
	else
		feed_the_only_exec_list_node_data(msh);
}
