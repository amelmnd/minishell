/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 10:47:52 by amennad           #+#    #+#             */
/*   Updated: 2023/09/14 22:06:06 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_int_len(long int n)
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

char	*itoa_logic(long int n, int n_len, char *result)
{
	if (n < 0)
	{
		result[0] = '-';
		n = n * (-1);
	}
	while (n > 0)
	{
		result[n_len] = n % 10 + 48;
		n = n / 10;
		n_len--;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	int			n_len;
	char		*result;
	long int	nb;

	nb = n;
	n_len = ft_int_len(nb);
	result = malloc(sizeof(char) * (n_len + 1));
	if (!result)
		return (NULL);
	result[n_len--] = '\0';
	if (n == 0)
	{
		result[0] = 48;
	}
	else
		itoa_logic(nb, n_len, result);
	return (result);
}
