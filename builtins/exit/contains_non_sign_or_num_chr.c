/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contains_non_sign_or_num_chr.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:18:23 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 15:55:22 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_diff_than_sign_or_num(char c)
{
	if (ft_isdigit(c) || c == '+' || c == '-')
		return (FALSE);
	return (TRUE);
}

void	contains_non_sign_or_num_chr(t_msh *msh)
{
	int		i;
	char	*htss;

	if (msh && msh->exit)
	{
		i = -1;
		htss = msh->exit->ht_spaces_stripped;
		while (htss[++i])
		{
			if (is_diff_than_sign_or_num(htss[i]))
				non_numeric_arg_assignation(msh);
		}
		
	}
}
