/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:29:06 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 01:20:43 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int print = 0; // à supprimer !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void	ft_execve(t_msh *msh, t_exec_list *exec_list_node)
{
	t_exec	*exec;

	if (msh && msh->exec && exec_list_node && exec_list_node->args_array)
	{
		exec = msh->exec;
		if (print) {dprintf(2, "ft_execve : Entrée\n");}
		if (print) {dprintf(2, "ft_execve : exec->cmd_path_ready = %s\n", exec->cmd_path_ready);}
		if (print) {dprintf(2, "ft_execve : exec_list_node->args_array[0] = %s ; exec_list_node->args_array[1] = %s\n", exec_list_node->args_array[0], exec_list_node->args_array[1]);}
		if (execve(exec->cmd_path_ready, 
			exec_list_node->args_array, msh->msh_env))
		{
			printf("minishell: execve: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	if (print) {dprintf(2, "ft_execve : après le execve ; perror puis exit imminent\n");}
}
