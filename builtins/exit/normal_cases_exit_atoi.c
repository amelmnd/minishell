/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_cases_exit_atoi.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:39:07 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 16:16:03 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_sign(char *arg)
{
	if (arg)
	{
		if (arg[0] == '-')
			return (-1);
	}
	return (1);
}

void	normal_cases_exit_atoi(t_msh *msh)
{
	int			i;
	long long	ret;
	char		*fzs;

	i = -1;
	ret = 0;
	fzs = msh->exit->front_zeros_stripped;
	while (fzs[++i] && msh->exit->tests_ok)
	{
		ret *= 10;
		if (!i && is_a_sign(fzs[i]))
			continue ;
		ret += fzs[i] - 48;
		if (ret < 0 || (i < msh->exit->len_fzs && ret >= 922337203685477580
				&& fzs[i + 1] > '7'))
		{
			non_numeric_arg_assignation(msh);
			return ;
		}
	}
	ret *= get_sign(fzs);
	msh->return_code = (int)(ret % 256);
}
