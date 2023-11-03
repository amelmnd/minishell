/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_full_blanks_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:00:48 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 18:00:55 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	is_a_blank(char c)
{
	return ((c >= 9 && c <= 13) || (c == ' '));
}

int	s_full_blanks(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!is_a_blank(s[i]))
			return (0);
	}
	return (1);
}
