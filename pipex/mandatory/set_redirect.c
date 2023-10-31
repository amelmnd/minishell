/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:18:06 by nstoutze          #+#    #+#             */
/*   Updated: 2023/07/02 16:55:30 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	set_redirect_first_cmd(t_ppx *ppx)
{
	ft_close(ppx, ppx->pipefd[READ]);
	ppx->fd_input = open(ppx->av[1], O_RDONLY);
	if (ppx->fd_input == -1)
	{
		first_file_open_failure_msg(ppx);
		ft_close(ppx, ppx->pipefd[WRITE]);
		exit(EXIT_FAILURE);
	}
	ft_duptwo(ppx, ppx->fd_input, STDIN_FILENO);
	ft_close(ppx, ppx->fd_input);
	ft_duptwo(ppx, ppx->pipefd[WRITE], STDOUT_FILENO);
	ft_close(ppx, ppx->pipefd[WRITE]);
}

static void	set_redirect_last_cmd(t_ppx *ppx)
{
	ft_close(ppx, ppx->pipefd[WRITE]);
	ft_close(ppx, ppx->pipefd[READ]);
	ft_duptwo(ppx, ppx->fd_temp, STDIN_FILENO);
	ft_close(ppx, ppx->fd_temp);
	ppx->fd_output = open(ppx->av[ppx->ac - 1], O_WRONLY | O_CREAT
			| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (ppx->fd_output == -1)
		last_file_open_failure_msg(ppx);
	ft_duptwo(ppx, ppx->fd_output, STDOUT_FILENO);
	ft_close(ppx, ppx->fd_output);
}

void	set_redirect(t_ppx *ppx)
{
	if (ppx->num_cmd == 2)
		set_redirect_first_cmd(ppx);
	else if (ppx->num_cmd == ppx->ac - 2)
		set_redirect_last_cmd(ppx);
}
