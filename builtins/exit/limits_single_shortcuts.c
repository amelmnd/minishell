/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits_single_shortcuts.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:36:15 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 11:05:50 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	limits_single_shortcuts(t_msh *msh)
{
	if (ft_strcmp(msh->exit->front_zeros_stripped, "-9223372036854775808"))
	{
		msh->return_code = 0;
		msh->exit->ready = TRUE;
	}
	else if (ft_strcmp(msh->exit->front_zeros_stripped,
			"-9223372036854775807"))
	{
		msh->return_code = 1;
		msh->exit->ready = TRUE;
	}
	else if (ft_strcmp(msh->exit->front_zeros_stripped,
			"9223372036854775807"))
	{
		msh->return_code = 255;
		msh->exit->ready = TRUE;
	}
}
