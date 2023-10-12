/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 08:55:34 by amennad           #+#    #+#             */
/*   Updated: 2023/04/04 14:07:02 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief
 *
 * @param haystack : where we search
 * @param needle : what we seek
 * @param len : what length are we looking for
 * @return char*
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	y;

	i = 0;
	if (!needle[0])
		return ((char *) &haystack[0]);
	if (len == 0 || !haystack[0])
		return (0);
	while (i < len && haystack[i])
	{
		y = 0;
		while (haystack[i + y] == needle[y] && (i + y) < len)
		{
			if (needle[y + 1] == '\0')
			{
				return ((char *)&haystack[i]);
			}
			y++;
		}
		i++;
	}
	return (0);
}
