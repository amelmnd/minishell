/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_variant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:09:32 by amennad           #+#    #+#             */
/*   Updated: 2023/09/14 22:02:52 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_int_len(long int n)
{
	int	i;

	i = 0;
	if (!n)
		return (1);
	if (n < 0)
	{
		n = n * (-1);
		i++;
	}
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_unsigned_itoa(unsigned int n)
{
	int					n_len;
	char				*result;
	long unsigned int	nb;

	nb = n;
	n_len = ft_int_len(nb);
	result = malloc(sizeof(char) * (n_len + 1));
	if (!result)
		return (0);
	result[n_len--] = '\0';
	if (n == 0)
	{
		result[0] = 48;
	}
	else
		itoa_logic((long int)nb, n_len, result);
	return (result);
}
