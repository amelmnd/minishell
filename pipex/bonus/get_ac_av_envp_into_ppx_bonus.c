/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ac_av_envp_into_ppx_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 09:00:56 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/23 20:15:28 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	get_ac_av_envp_into_ppx(t_ppx *ppx, int ac, char **av, char **envp)
{
	ppx->ac = ac;
	ppx->av = ntcharss_copy(ppx, av);
	ppx->envp = ntcharss_copy(ppx, envp);
}
