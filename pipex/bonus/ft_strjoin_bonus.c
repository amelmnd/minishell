/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:05:52 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/25 15:30:49 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strjoin(t_ppx *ppx, char *s1, char const *s2)
{
	char	*join;
	size_t	total_size;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = -1;
	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *)malloc(sizeof(char) * total_size);
	if (!join)
		errormsg_free_exit(ppx, "bash");
	while (++i < (size_t)ft_strlen(s1))
		join[i] = s1[i];
	while (++j < (size_t)ft_strlen(s2))
		join[i + j] = s2[j];
	join[i + j] = '\0';
	return (join);
}
