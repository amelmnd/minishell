/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ntcharss.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:36:30 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/05 16:39:40 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ntcharss(char ***dust)
{
	int	i;

	if (*dust && (*dust)[0])
	{
		i = -1;
		while ((*dust)[++i])
		{
			free((*dust)[i]);
			(*dust)[i] = NULL;
		}
		free(*dust);
	}
	*dust = NULL;
}
