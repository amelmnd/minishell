/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:29:55 by amennad           #+#    #+#             */
/*   Updated: 2023/04/12 12:59:33 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static int	char_in_set(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	start = 0;
	if (!s1 || !*s1)
		return (ft_strdup(""));
	if (s1 && set)
	{
		while (char_in_set(s1[start], set) == 1)
			start++;
		end = ft_strlen(s1) - 1;
		while (char_in_set(s1[end], set) == 1)
			end--;
		if (end < start)
			return ("");
		str = ft_substr(s1, start, end - start + 1);
		return (str);
	}
	else
	{
		return (NULL);
	}
}
