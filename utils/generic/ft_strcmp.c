/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:38:23 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/24 20:23:10 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//return 1 if s1 and s2 are the same
//return 0 otherwise
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i] || s2[i])
		return (0);
	return (1);
}
