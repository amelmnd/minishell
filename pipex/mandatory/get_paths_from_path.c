/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths_from_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:21:07 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/20 15:39:43 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	get_paths_from_path(t_ppx *ppx)
{
	if (ppx->path_from_envp)
		ppx->paths_from_path = ft_split(ppx, ppx->path_from_envp, ':');
}
