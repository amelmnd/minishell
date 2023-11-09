/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_full_null_charss.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:29:05 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/08 14:29:38 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**malloc_full_null_charss(int size)
{
	char	**array;
	int		i;

	array = NULL;
	i = -1;
	if (size)
	{
		array = (char **)malloc(sizeof(char *) * (size + 1));
		if (!array)
			return (NULL);
	}
	while (++i < size)
		array[i] = NULL;
	array[size] = NULL;
	return (array);
}
