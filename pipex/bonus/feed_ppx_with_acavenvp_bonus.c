/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feed_ppx_with_acavenvp_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:34:25 by nstoutze          #+#    #+#             */
/*   Updated: 2023/07/01 17:35:06 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	feed_ppx_with_acavenvp(t_ppx *ppx, int ac, char **av, char **envp)
{
	get_ac_av_envp_into_ppx(ppx, ac, av, envp);
	if (envp)
	{
		get_path_from_envp(ppx);
		get_paths_from_path(ppx);
	}
}
