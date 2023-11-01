/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:46:17 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 17:50:01 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	if (!s1 && !s2)
		return (1);
	if (!s1 ^ !s2)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[++i] && s2[i] && s1[i] == s2[i])
		;
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}
