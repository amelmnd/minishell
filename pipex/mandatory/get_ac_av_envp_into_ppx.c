/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ac_av_envp_into_ppx.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 09:00:56 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 19:47:53 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	get_ac_av_envp_into_ppx(t_ppx *ppx, int ac, char **av, char **envp)
{
	ppx->ac = ac;
	ppx->av = ntcharss_copy(ppx, av);
	ppx->envp = ntcharss_copy(ppx, envp);
}
