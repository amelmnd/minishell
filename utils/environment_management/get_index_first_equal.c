/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_index_first_equal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 05:15:12 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/25 05:15:23 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_index_first_equal(char *str)
{
	int	index_first_equal;

	index_first_equal = -1;
	while (str && str[++index_first_equal])
	{
		if (str[index_first_equal] == '=')
			return (index_first_equal);
	}
	return (0);
}
