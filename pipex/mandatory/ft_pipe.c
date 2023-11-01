/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:09:31 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 19:47:28 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_pipe(t_ppx *ppx)
{
	if (pipe(ppx->pipefd) == -1)
		errormsg_free_exit(ppx, "bash");
}
