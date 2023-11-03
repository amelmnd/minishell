/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_unset_mode_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:45:22 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 22:36:26 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	pum_first_file(t_ppx *ppx)
{
	int	fd_first_file;

	fd_first_file = open(ppx->av[1], O_RDONLY);
	if (fd_first_file != -1)
	{
		nsfod_msg(ppx, 2);
		close(fd_first_file);
	}
	else if (errno == EACCES)
		permission_denied_msg(ppx, 1);
	else if (errno == ENOENT)
		nsfod_msg(ppx, 1);
}

static void	pum_last_file(t_ppx *ppx)
{
	int	fd_last_file;

	fd_last_file = open(ppx->av[ppx->ac - 1], O_WRONLY);
	if (fd_last_file != -1)
	{
		nsfod_msg(ppx, ppx->ac - 2);
		close(fd_last_file);
	}
	else if (errno == EACCES)
		permission_denied_msg(ppx, ppx->ac - 1);
	else if (errno == ENOENT)
		nsfod_msg(ppx, ppx->ac - 1);
}

void	path_unset_mode(t_ppx *ppx)
{
	ppx->i = 2;
	if (!ppx->here_doc)
		pum_first_file(ppx);
	while (++(ppx->i) <= ppx->ac - 3)
		nsfod_msg(ppx, ppx->i);
	pum_last_file(ppx);
}
