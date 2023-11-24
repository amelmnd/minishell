/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:32:57 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/24 07:33:07 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit(t_msh *msh)
{
	if (msh && msh->exit)
	{
		free_chars(&(msh->exit->ht_spaces_stripped));
		free_chars(&(msh->exit->front_zeros_stripped));
		free(msh->exit);
		msh->exit = NULL;
	}
}
