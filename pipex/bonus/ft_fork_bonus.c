/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:11:37 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/25 15:30:26 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_fork(t_ppx *ppx)
{
	ppx->child = fork();
	if (ppx->child == -1)
		errormsg_free_exit(ppx, "bash");
}
