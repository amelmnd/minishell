/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_ntcharss.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 23:05:16 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/20 15:39:47 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	get_size_ntcharss(char **ntcharss)
{
	int	i;

	i = 0;
	while (ntcharss[i])
		i++;
	return (i);
}
