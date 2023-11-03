/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:04:32 by nstoutze          #+#    #+#             */
/*   Updated: 2023/07/02 16:58:01 by nstoutze         ###   ########.fr       */
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
		if ((ppx->num_cmd >= 3) && (ppx->fd_temp_duplicated))
			ft_close(ppx, ppx->fd_temp);
		ppx->fd_temp = ppx->pipefd[READ];
		ppx->fd_temp_duplicated = 1;
		free_after_iteration(ppx);
	}
}

void	feed_ppx_with_acavenvp(t_ppx *ppx, int ac, char **av, char **envp)
{
	get_ac_av_envp_into_ppx(ppx, ac, av, envp);
	if (envp)
	{
		get_path_from_envp(ppx);
		get_paths_from_path(ppx);
	}
}

void	pipex(int ac, char **av, char **envp)
{
	t_ppx	*ppx;

	ppx = NULL;
	if (ac == 5)
	{
		ppx = new_ppx();
		initialize_ppx(ppx);
		feed_ppx_with_acavenvp(ppx, ac, av, envp);
		pipex_loop(ppx);
		ft_close(ppx, ppx->pipefd[READ]);
		while (waitpid(-1, NULL, 0) != -1)
			;
		free_ppx(ppx);
	}
	else
		invalid_number_of_argument_msg();
}
