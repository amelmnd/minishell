/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntcharss_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 23:04:13 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 19:49:32 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**ntcharss_copy(t_ppx *ppx, char **ntcharss_to_copy)
{
	char	**copy;
	int		len_to_copy;

	len_to_copy = get_size_ntcharss(ntcharss_to_copy);
	copy = (char **)malloc(sizeof(char *) * (len_to_copy + 1));
	if (!copy)
		errormsg_free_exit(ppx, "bash");
	len_to_copy = -1;
	while (ntcharss_to_copy[++len_to_copy])
		copy[len_to_copy] = ft_strdup(ppx, ntcharss_to_copy[len_to_copy]);
	copy[len_to_copy] = NULL;
	return (copy);
}
