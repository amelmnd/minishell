/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:05:50 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/25 15:31:45 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	gnl_strlen(char *s)
{
	size_t	l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		else
			i++;
	}
	return (NULL);
}

char	*gnl_strdup(t_ppx *ppx, char *s)
{
	char	*str;
	int		i;
	int		slen;

	if (!s)
		return (NULL);
	i = -1;
	slen = 0;
	while (s[slen])
		slen++;
	str = malloc(sizeof(char) * (slen + 1));
	if (!str)
		errormsg_free_exit(ppx, "bash");
	else
	{
		while (s[++i])
			str[i] = s[i];
		str[i] = '\0';
	}
	return (str);
}

char	*gnl_strjoin(t_ppx *ppx, char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;
	size_t	lens1;
	size_t	lens2;

	lens1 = gnl_strlen(s1);
	lens2 = gnl_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = -1;
	join = (char *)malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!join)
		errormsg_free_exit(ppx, "bash");
	while (++i < lens1)
		join[i] = s1[i];
	while (++j < lens2)
		join[i + j] = s2[j];
	join[i + j] = '\0';
	if (s1)
		free(s1);
	return (join);
}

char	*gnl_substr(t_ppx *ppx, char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	slen = gnl_strlen(s);
	if ((size_t)start >= slen)
		return (NULL);
	if (slen - (size_t)start > len)
		sub = (char *)malloc(sizeof(char) * (len + 1));
	else
		sub = (char *)malloc(sizeof(char) * (slen - (size_t)start + 1));
	if (!sub)
		errormsg_free_exit(ppx, "bash");
	i = -1;
	while (++i < len && s[start])
	{
		sub[i] = s[start];
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
