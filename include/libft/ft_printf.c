/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:09:32 by amennad           #+#    #+#             */
/*   Updated: 2023/09/15 09:58:36 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_print_line(char check_char, va_list args, int *len)
{
	if (check_char == 'c')
		check_c(va_arg(args, int), len);
	if (check_char == '%')
		check_c('%', len);
	if (check_char == 's')
		check_s(va_arg(args, char *), len);
	if (check_char == 'i' || check_char == 'd')
		temp_str(ft_itoa(va_arg(args, int)), len);
	if (check_char == 'u')
		temp_str(ft_unsigned_itoa(va_arg(args, int)), len);
	if (check_char == 'x')
		convert_base_x(va_arg(args, unsigned int), "0123456789abcdef", len);
	if (check_char == 'X')
		convert_base_x(va_arg(args, unsigned int), "0123456789ABCDEF", len);
	if (check_char == 'p')
	{
		*len += 2;
		ft_putstr("0x");
		convert_base_p(va_arg(args, unsigned long int), len);
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		length;
	int		i;

	length = 0;
	i = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		length++;
		if (format[i] == '%')
		{
			length--;
			ft_print_line(format[i + 1], args, &length);
			i++;
		}
		else
			ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (length);
}
