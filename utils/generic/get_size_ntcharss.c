/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_ntcharss.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:20:45 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 12:20:52 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size_ntcharss(char **ntcharss)
{
	int	i;

	i = 0;
	while (ntcharss[i])
		i++;
	return (i);
}
