/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_than_one_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:20:25 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 11:05:56 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_a_sign(char c)
{
	return (c == '+' || c == '-');
}

int	nb_signs_in_str(char *str)
{
	int	nb_signs;
	int	i;

	nb_signs = 0;
	i = -1;
	while (str[++i])
	{
		if (is_a_sign(str[i]))
			nb_signs++;
	}
	return (nb_signs);
}

void	more_than_one_sign(t_msh *msh)
{
	if (nb_signs_in_str(msh->exit->ht_spaces_stripped) > 1)
		non_numeric_arg_assignation(msh);
}
