/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_numeric_arg_assignation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:42:12 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 10:42:21 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	non_numeric_arg_assignation(t_msh *msh)
{
	if (msh && msh->exit)
	{
		msh->return_code = 2;
		msh->exit->tests_ok = FALSE;
	}
}
