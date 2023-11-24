/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:18:22 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/19 23:18:23 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_chars(char **dust)
{
	if (*dust)
	{
		free(*dust);
		*dust = NULL;
	}
}