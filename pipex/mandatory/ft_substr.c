/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:04:46 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 19:47:50 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_substr(t_ppx *ppx, char const *s, int start, int len)
{
	char	*sub;
	int		slen;
	int		i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (NULL);
	if (slen - start > len)
		sub = (char *)malloc(sizeof(char) * (len + 1));
	else
		sub = (char *)malloc(sizeof(char) * (slen - start + 1));
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
