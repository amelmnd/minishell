/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:25:54 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 01:17:24 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_exec(t_exec *exec)
{
	if (exec)
	{
		exec->path_defined = TRUE;
		exec->path_from_mshenv = NULL;
		exec->paths_from_path = NULL;
		exec->pipefd[0] = 0;
		exec->pipefd[1] = 0;
		exec->fd_temp = -1;
		exec->fd_read_redirect = -1;
		exec->fd_write_redirect = -1;
		exec->cmd_path_ready = NULL;
		exec->pid_t_array = NULL;
	}
}

t_exec	*new_exec(void)
{
	t_exec	*new;

	new = NULL;
	new = (t_exec *)malloc(sizeof(t_exec));
	if (!new)
		return (NULL);
	init_exec(new);
	return (new);
}
