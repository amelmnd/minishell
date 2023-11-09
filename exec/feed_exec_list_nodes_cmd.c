/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feed_exec_list_nodes_cmd.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:29:09 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/07 18:29:40 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	feed_exec_list_node_cmd(t_msh *msh)
{
	t_exp_list	*exp_list_node;
	t_exec_list	*exec_list_node;

	exp_list_node = msh->exp_list;
	exec_list_node = msh->exec_list;
	if (msh && msh->exp_list && msh->exec_list)
	{
		while (exp_list_node)
		{
			if (exp_list_node->exp_type == PIPE_EXPANDED)
				exec_list_node = exec_list_node->next;
			else if (exp_list_node->exp_type == WORD_EXPANDED)
			{
				exec_list_node->cmd = ft_strdup(exp_list_node->str);
				exec_list_node = exec_list_node->next;
				while (exp_list_node && exp_list_node->exp_type != PIPE_EXPANDED)
					exp_list_node = exp_list_node->next;
			}
			if (exp_list_node)
				exp_list_node = exp_list_node->next;
		}
	}
}

static void	feed_the_only_exec_list_node_cmd(t_msh *msh)
{
	t_exp_list	*exp_list_node;

	exp_list_node = msh->exp_list;
	if (msh && msh->exp_list && msh->exec_list)
	{
		while (exp_list_node)
		{
			if (exp_list_node->exp_type == WORD_EXPANDED)
			{
				msh->exec_list->cmd = ft_strdup(exp_list_node->str);
				break ;
			}
			exp_list_node = exp_list_node->next;
		}
	}
}

void	feed_exec_list_nodes_cmd(t_msh *msh)
{
	if (msh && msh->exec_list && msh->exec_list->nb_pipes)
		feed_exec_list_node_cmd(msh);
	else
		feed_the_only_exec_list_node_cmd(msh);
}
