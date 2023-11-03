/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:01:48 by amennad           #+#    #+#             */
/*   Updated: 2023/11/03 21:30:06 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*copy;

	i = 0;
	copy = (char *) malloc(sizeof(char) *(ft_strlen(s1)) + 1);
	if (!copy)
		return (NULL);
	while (i < (int)ft_strlen(s1))
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

// commentaire à virer!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*
char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	if (!s)
		return (NULL);
	dup = NULL;
	dup = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dup)
		return (NULL);
	i = -1;
	while (s[++i])
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}
*/
