/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:14:38 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 15:57:06 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	arg_full_of_spaces(t_msh *msh, char *arg)
{
	int	i;

	if (msh)
	{
		i = -1;
		while (arg[++i])
		{
			if (arg[i] != ' ')
				return ;
		}
		non_numeric_arg_assignation(msh);
	}
}

static void	length_zero(t_msh *msh, char *arg)
{
	if (msh)
	{
		if (!ft_strlen(arg))
			non_numeric_arg_assignation(msh);
	}
}

static void	lenght_one_digit(t_msh *msh, char *arg)
{
	if (msh && msh->exit)
	{
		if (ft_strlen(arg) == 1 && ft_isdigit(arg[0]))
		{
			msh->return_code = (int)(arg[0] - 48);
			msh->exit->ready = TRUE;
		}
		else if (ft_strlen(arg) == 1)
			non_numeric_arg_assignation(msh);
	}		
}

void	easy_tests(t_msh *msh, char *arg)
{
	if (msh && msh->exit)
	{
		if (msh->exit->tests_ok)
			arg_full_of_spaces(msh, arg);
		if (msh->exit->tests_ok)
			length_zero(msh, arg);
		if (msh->exit->tests_ok)
			lenght_one_digit(msh, arg);
	}
}
