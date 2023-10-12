/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 08:55:44 by amennad           #+#    #+#             */
/*   Updated: 2023/04/08 12:25:12 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief
 *
 * @param count : nb d'éléments consécutifs à réserver dans le bloc de mémoire
 * @param size : fixer la taille (en nombre d'octets) d'un élément
 * @return void*
 */
void	*ft_calloc(size_t count, size_t size)
{
	size_t	*element;

	if (size == SIZE_MAX)
		count = 1;
	element = (void *) malloc(count * size);
	if (!element)
		return (NULL);
	ft_bzero(element, count * size);
	return ((void *) element);
}
