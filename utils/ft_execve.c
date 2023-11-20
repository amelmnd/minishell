/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:29:06 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/20 00:02:11 by nstoutze         ###   ########.fr       */
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
			printf("minishell: execve: %s\n", strerror(errno)); // ft_putstr_fd
			exit(EXIT_FAILURE);
		}
	}
}
