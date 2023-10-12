/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:40:55 by amennad           #+#    #+#             */
/*   Updated: 2023/09/15 10:22:07 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *str)
{
	int	i;
	int	is_neg;
	int	result;

	i = 0;
	is_neg = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		is_neg = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result + (str[i] - 48);
		i++;
		if (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
			result = result * 10;
		if (result > 2147483647)
			return (-2147483648);
	}
	if (is_neg == 1)
		return (result * -1);
	return (result);
}
