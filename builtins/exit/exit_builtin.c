/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:32:25 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 16:17:03 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	parsing_arg(t_msh *msh, char *arg)
{
	if (msh && msh->exit)
	{
		easy_tests(msh, arg);
		if (msh->exit->tests_ok && !(msh->exit->ready))
			ht_spaces_stripped_parsing(msh, arg);
		if (msh->exit->tests_ok && !(msh->exit->ready))
			front_zeros_stripped_parsing(msh);
		if (msh->exit->tests_ok && !(msh->exit->ready))
			limits_single_shortcuts(msh);
		if (msh->exit->tests_ok && !(msh->exit->ready))
			normal_cases_exit_atoi(msh);
		return (msh->exit->tests_ok);
	}
	return (FALSE);
}

static t_exit	*new_exit_struct(void)
{
	t_exit	*new;

	new = NULL;
	new = (t_exit *)malloc(sizeof(t_exit));
	if (!new)
		return (NULL);
	new->ready = FALSE;
	new->tests_ok = TRUE;
	new->ht_spaces_stripped = NULL;
	new->front_zeros_stripped = NULL;
	return (new);
}

static void	num_arg_required_errmsg(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

static void	too_many_args_errmsg(t_msh *msh)
{
	if (msh)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		msh->return_code = 1;
	}
}

void	exit_builtin(t_msh *msh, t_exec_list *exec_list_node)
{
	int	return_code;

	msh->exit = new_exit_struct();
	if (msh && exec_list_node)
	{
		if (exec_list_node->nb_words == 1)
			msh->return_code = 0;
		else if (exec_list_node->nb_words == 2)
		{
			if (!parsing_arg(msh, exec_list_node->args_array[1]))
				num_arg_required_errmsg(exec_list_node->args_array[1]);
		}
		else if (exec_list_node->nb_words > 2)
		{
			if (parsing_arg(msh, exec_list_node->args_array[1]))
				too_many_args_errmsg(msh);
			else
				num_arg_required_errmsg(exec_list_node->args_array[1]);
		}
		return_code = msh->return_code;
		free_msh(msh);
		exit(return_code);
	}
}
