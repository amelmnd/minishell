/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open_failure_msg_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:28:35 by nstoutze          #+#    #+#             */
/*   Updated: 2023/07/02 18:25:08 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	first_file_open_failure_msg(t_ppx *ppx)
{
	write(2, "bash: ", 6);
	write(2, ppx->av[1], ft_strlen(ppx->av[1]));
	write(2, ": ", 2);
	perror("");
}

void	last_file_open_failure_msg(t_ppx *ppx)
{
	write(2, "bash: ", 6);
	write(2, ppx->av[ppx->ac - 1], ft_strlen(ppx->av[ppx->ac - 1]));
	write(2, ": ", 2);
	perror("");
}
