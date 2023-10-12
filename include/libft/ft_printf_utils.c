/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:04:13 by amennad           #+#    #+#             */
/*   Updated: 2023/09/14 19:45:17 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	check_c(char c, int *len)
{
	ft_putchar(c);
	*len += 1;
}

void	check_s(char *element, int *len)
{
	if (!element)
	{
		ft_putstr("(null)");
		*len += ft_strlen("(null)");
	}
	else
	{
		*len += ft_strlen(element);
		ft_putstr(element);
	}
}

void	temp_str(char *fn, int *len)
{
	char	*str;

	str = fn;
	*len += ft_strlen(str);
	ft_putstr(str);
	free(str);
}

void	convert_base_x(unsigned int n, char *base, int *len)
{
	unsigned int	len_base;

	len_base = ft_strlen(base);
	if (n >= len_base)
		convert_base_x(n / len_base, base, len);
	ft_putchar(base[n % len_base]);
	*len = *len + 1;
}

void	convert_base_p(unsigned long int n, int *len)
{
	char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
		convert_base_p(n / 16, len);
	ft_putchar(base[n % 16]);
	*len = *len + 1;
}
