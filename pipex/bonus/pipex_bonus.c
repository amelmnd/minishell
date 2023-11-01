/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:04:32 by nstoutze          #+#    #+#             */
/*   Updated: 2023/10/14 16:11:46 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	pipex_loop(t_ppx *ppx)
{
	while (++(ppx->num_cmd) < ppx->ac - 1)
	{
		ft_pipe(ppx);
		ft_fork(ppx);
		if (!ppx->child)
		{
			set_redirect(ppx);
			if (cmd_parsing(ppx))
				ft_execve(ppx);
			else
				exit(EXIT_FAILURE);
		}
		ft_close(ppx, ppx->pipefd[WRITE]);
		ft_close(ppx, ppx->fd_temp);
		ft_duptwo(ppx, ppx->pipefd[READ], ppx->fd_temp);
		close(ppx->pipefd[READ]);
		free_after_iteration(ppx); // a tester en commentant
	}
}

static void	last_file_management(t_ppx *ppx)
{
	int	last_file_status;

	if (ppx->here_doc)
		last_file_status = open(ppx->av[ppx->ac - 1], O_WRONLY 
				| O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		last_file_status = open(ppx->av[ppx->ac - 1], O_WRONLY 
				| O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (last_file_status == -1 && errno == EACCES)
		last_file_open_failure_msg(ppx);
}

void	pipex_bonus(t_ppx *ppx)
{
	if (ft_strcmp(ppx->av[1], "here_doc") && ppx->ac < 6)
		invalid_number_of_argument_msg_bonus();
	else
	{
		if (ft_strcmp(ppx->av[1], "here_doc"))
			get_here_doc_content(ppx);
		last_file_management(ppx);
		pipex_loop(ppx);
		close(ppx->fd_temp);
		close(ppx->pipefd[READ]);
		close(ppx->pipefd[WRITE]);
	}
}
