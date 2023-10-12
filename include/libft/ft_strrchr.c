/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:24:02 by amennad           #+#    #+#             */
/*   Updated: 2023/04/05 11:40:18 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	s_len;

	s_len = ft_strlen(s);
	while (s_len > 0)
	{
		if (s[s_len] == (char) c)
		{
			return ((char *) &s[s_len]);
		}
		s_len--;
	}
	if (s[s_len] == (char) c)
	{
		return ((char *) &s[s_len]);
	}
	return (0);
}
