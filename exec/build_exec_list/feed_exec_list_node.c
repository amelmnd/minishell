/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feed_exec_list_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:48:14 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/19 22:31:59 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_a(int *arg_i, char *arg, t_exec_list *ex)
{
	if (ex)
	{
		ex->args_array[*arg_i] = ft_strdup(arg);
		(*arg_i)++;
	}
}

static void	add_r(int *red, t_exp_list *exp, t_exec_list *ex)
{
	if (exp && ex)
	{
		ex->redir_array[*red].exp_type = exp->exp_type;
		ex->redir_array[*red].str = ft_strdup(exp->str);
		(*red)++;
	}
}

static t_bool	feln_check_and_init(t_msh *msh, int *red_i, int *args_i)
{
	*red_i = 0;
	*args_i = 0;
	if (msh && msh->exp_list && msh->exec_list)
		return (TRUE);
	return (FALSE);
}

void	feed_exec_list_node(t_msh *msh)
{
	t_exp_list	*exp_list_node;
	t_exec_list	*exec_list_node;
	int			redirect_i;
	int			args_i;

	if (!feln_check_and_init(msh, &redirect_i, &args_i))
		return ;
	exp_list_node = msh->exp_list;
	exec_list_node = msh->exec_list;
	while (exp_list_node)
	{
		if (exp_list_node->exp_type == WORD_EXPANDED)
			add_a(&args_i, exp_list_node->str, exec_list_node);
		else if (exp_list_node->exp_type != PIPE_EXPANDED)
			add_r(&redirect_i, exp_list_node, exec_list_node);
		else if (exp_list_node->exp_type == PIPE_EXPANDED)
		{
			exec_list_node = exec_list_node->next;
			reset_counts(&args_i, &redirect_i);
		}
		exp_list_node = exp_list_node->next;
	}
}
