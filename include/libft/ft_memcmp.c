/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:07:30 by amennad           #+#    #+#             */
/*   Updated: 2023/04/10 09:26:24 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *pointer1, const void *pointer2, size_t size)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	s1 = (unsigned char *)pointer1;
	s2 = (unsigned char *)pointer2;
	while (i < size)
	{
		if (s1[i] != s2[i])
			return ((s1)[i] - (s2)[i]);
		i++;
	}
	return (0);
}
