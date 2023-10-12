/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:41:22 by amennad           #+#    #+#             */
/*   Updated: 2023/09/14 22:07:01 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	nb_str(char *str, char c)
{
	int	i;
	int	nb_word;

	i = 0;
	nb_word = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
		{
			nb_word++;
		}
		i++;
	}
	return (nb_word);
}

void	testfac(char *str, char sep, int tab_size, char **tab)
{
	int	i;
	int	startword;
	int	len_world;
	int	j;

	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		len_world = 0;
		if (str[i] == sep)
			i++;
		startword = i;
		if (str[i] != sep)
		{
			while (str[i] != sep && str[i] != '\0')
			{
				len_world++;
				if ((str[i + 1] == sep || str[i + 1] == '\0') && j < tab_size)
					tab[j++] = ft_substr(str, startword, len_world);
				i++;
			}
		}
	}
	tab[j] = (NULL);
}

char	**ft_split(char const *s, char sep)
{
	int		tab_size;
	char	*str;
	char	**tab;
	char	**error;

	str = (char *)s;
	if (!str)
	{
		error = (char **)ft_calloc(1, sizeof(char *));
		return (error);
	}
	tab_size = nb_str(str, sep);
	if (tab_size == 0)
	{
		error = (char **)ft_calloc(1, sizeof(char *));
		return (error);
	}
	tab = (char **)ft_calloc(tab_size + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	testfac(str, sep, tab_size, tab);
	return (tab);
}
