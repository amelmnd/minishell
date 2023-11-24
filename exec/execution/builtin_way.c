/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_way.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:59:06 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/23 15:50:17 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	norminette_pleasing(t_msh *msh, t_exec_list *exec_list_node)
{
	t_bool	builtin;

	builtin = TRUE;
	if (msh && exec_list_node)
	{
		if (ft_strcmp(exec_list_node->cmd, "export"))
			export_builtin(msh, exec_list_node);
		else if (ft_strcmp(exec_list_node->cmd, "unset"))
			unset_builtin(msh, exec_list_node);
		else if (ft_strcmp(exec_list_node->cmd, "env")
			|| ft_strcmp(exec_list_node->cmd, "/bin/env"))
			env_builtin(msh, exec_list_node);
		else if (ft_strcmp(exec_list_node->cmd, "exit"))
			exit_builtin(msh, exec_list_node);
		else
			builtin = FALSE;
	}
	return (builtin);
}

void	builtin_way(t_msh *msh, t_exec_list *exec_list_node)
{
	t_bool	builtin;

	builtin = TRUE;
	if (msh && exec_list_node)
	{
		if (ft_strcmp(exec_list_node->cmd, "echo")
			|| ft_strcmp(exec_list_node->cmd, "/bin/echo"))
			echo_builtin(msh, exec_list_node);
		else if (ft_strcmp(exec_list_node->cmd, "cd"))
			cd_builtin(msh, exec_list_node);
		else if (ft_strcmp(exec_list_node->cmd, "pwd"))
			pwd_builtin(msh, exec_list_node);
		else if (!(norminette_pleasing(msh, exec_list_node)))
			builtin = FALSE;
	}
	if (builtin)
		exit(msh->return_code);
}
