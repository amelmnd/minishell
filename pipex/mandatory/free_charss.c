/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_charss.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:26:07 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 19:46:47 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_charss(char ***dust)
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
