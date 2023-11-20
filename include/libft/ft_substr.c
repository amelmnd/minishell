/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:16:55 by amennad           #+#    #+#             */
/*   Updated: 2023/09/14 19:32:39 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief
 *
 * @param s : La chaîne de laquelle extraire la nouvelle chaîne
 * @param start : L’index de début de la nouvelle chaîne dans la chaîne ’s’
 * @param len : La taille maximale de la nouvelle chaîne
 * @return char*
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*result;

	i = 0;
	if (!s)
		return (ft_strdup(""));
	if (start > (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (len > (unsigned int)ft_strlen(s))
		result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	else
		result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
S EXISTE Sinon NULL
strart len s 0
stdup retune
*/
