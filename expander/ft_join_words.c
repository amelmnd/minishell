/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:17:46 by amennad           #+#    #+#             */
/*   Updated: 2023/10/28 16:10:52 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_word(char *s1, char *s2)
{
	int		i;
	int		y;
	char	*result;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[y] != '\0')
	{
		result[i + y] = s2[y];
		y++;
	}
	result[i + y] = '\0';
	return (result);
}

char	*ft_one_word(char *s1)
{
	int		i;
	char	*result;

	i = 0;
	if (!s1)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!result)
		return (NULL);
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
