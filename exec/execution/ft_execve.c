/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:29:06 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 12:42:33 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_msh *msh, t_exec_list *exec_list_node)
{
	t_exec	*exec;

	if (msh && msh->exec && exec_list_node && exec_list_node->args_array)
	{
		exec = msh->exec;
		if (execve(exec->cmd_path_ready,
				exec_list_node->args_array, msh->msh_env))
		{
			ft_putstr_fd("minishell: execve: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			exit(EXIT_FAILURE);
		}
	}
}
