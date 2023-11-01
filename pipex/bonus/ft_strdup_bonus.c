/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:04:02 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/25 15:30:43 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strdup(t_ppx *ppx, const char *s)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = ft_strlen(s);
	i = -1;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		errormsg_free_exit(ppx, "bash");
	while (++i < len)
		dup[i] = s[i];
	dup[len] = '\0';
	return (dup);
}
