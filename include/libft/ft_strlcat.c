/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:23:32 by amennad           #+#    #+#             */
/*   Updated: 2023/09/14 22:06:17 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_total;

	i = 0;
	len_total = ft_strlen(dst);
	if (dstsize <= len_total)
		return (dstsize + ft_strlen(src));
	while (src[i] != '\0' && len_total + 1 < dstsize)
	{
		dst[len_total] = src[i];
		len_total++;
		i++;
	}
	dst[len_total] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
