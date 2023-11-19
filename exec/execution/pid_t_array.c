/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_t_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:58:03 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/19 20:58:14 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_and_get_the_last_return_code(t_msh *msh)
{
	int		status;
	pid_t	pid;
	int		last_exit_status;

	if (msh && msh->exec)
	{
		pid = waitpid(-1, &status, 0);
		while (pid != -1)
		{
			if (WIFEXITED(status))
			{
				if (pid == msh->exec->last_child)
					last_exit_status = WEXITSTATUS(status);
			}
			pid = waitpid(-1, &status, 0);
		}
		msh->return_code = last_exit_status;
	}
}

void	create_pid_t_array(t_msh *msh)
{
	int	nb_childs;

	if (msh && msh->exec && msh->exec_list)
	{
		nb_childs = msh->exec_list->nb_pipes + 1;
		msh->exec->pid_t_array = (pid_t *)malloc(sizeof(pid_t) * nb_childs);
		if (!(msh->exec->pid_t_array))
			return ;
		while (--nb_childs >= 0)
			msh->exec->pid_t_array[nb_childs] = -1;
	}
}
