/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 07:20:46 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/24 07:20:56 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(t_msh *msh)
{
	if (msh && msh->exec)
	{
		free_chars(&(msh->exec->path_from_mshenv));
		free_ntcharss(&(msh->exec->paths_from_path));
		free_chars(&(msh->exec->cmd_path_ready));
		free_ints(&(msh->exec->pid_t_array));
		free(msh->exec->s_path_stat);
		free(msh->exec);
		msh->exec = NULL;
	}
}
