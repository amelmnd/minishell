/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_ppx_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:25:38 by nstoutze          #+#    #+#             */
/*   Updated: 2023/07/02 18:32:17 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	initialize_ppx(t_ppx *ppx)
{
	ppx->av = NULL;
	ppx->envp = NULL;
	ppx->slash_and_cmd = NULL;
	ppx->args = NULL;
	ppx->chars_temp = NULL;
	ppx->path_from_envp = NULL;
	ppx->paths_from_path = NULL;
	ppx->abs_path_cmd = NULL;
	ppx->delimiter = NULL;
	ppx->hdc = NULL;
	ppx->path_defined = 0;
	ppx->i = 0;
	ppx->ac = 0;
	ppx->pipefd[0] = 0;
	ppx->pipefd[1] = 0;
	ppx->child = -2;
	ppx->fd_input = -2;
	ppx->fd_output = -2;
	ppx->fd_temp = open(".temp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	ppx->num_cmd = 1;
	ppx->fd_temp_duplicated = 0;
	ppx->here_doc = 0;
}
