/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:02:11 by amennad           #+#    #+#             */
/*   Updated: 2023/09/14 19:45:17 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// void	ft_putchar(char c)
// {
// 	write(1, &c, 1);
// }

// void	ft_putstr(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		write(1, &s[i], 1);
// 		i++;
// 	}
// }

// void	ft_putnbr(int n)
// {
// 	if (n == -2147483648)
// 		ft_putstr("-2147483648");
// 	else if (n < 0)
// 	{
// 		ft_putchar('-');
// 		ft_putnbr(-n);
// 	}
// 	else if (n >= 10)
// 	{
// 		ft_putnbr(n / 10);
// 		ft_putchar(n % 10 + '0');
// 	}
// 	else
// 		ft_putchar(n + '0');
// }

int	ft_unsigned_putnbr(int n)
{
	int	i;

	i = 0;
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
		i++;
	}
	else
	{
		ft_putchar(n + '0');
		i++;
	}
	return (i);
}
