/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntcharss_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:22:01 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 12:22:10 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ntcharss_copy(char **ntcharss_to_copy)
{
	char	**copy;
	int		len_to_copy;

	if (!ntcharss_to_copy)
		return (NULL);
	len_to_copy = get_size_ntcharss(ntcharss_to_copy);
	copy = (char **)malloc(sizeof(char *) * (len_to_copy + 1));
	if (!copy)
		return (NULL);
	len_to_copy = -1;
	while (ntcharss_to_copy[++len_to_copy])
		copy[len_to_copy] = ft_strdup(ntcharss_to_copy[len_to_copy]);
	copy[len_to_copy] = NULL;
	return (copy);
}
