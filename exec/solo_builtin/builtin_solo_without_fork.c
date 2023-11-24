/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_solo_without_fork.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:46:06 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/24 16:39:17 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	norminette_pleasing(t_exec_list *exec_list_node, t_bool *bool)
{
	if (exec_list_node)
	{
		if (get_size_ntcharss(exec_list_node->args_array) > 1)
			*bool = TRUE;
		else
			*bool = FALSE;
	}
	else
		*bool = FALSE;
}

static t_bool	is_cmd_in_nfsolobuiltin_list(t_exec_list *exec_list_node)
{
	char	*cmd;
	t_bool	bool;

	cmd = NULL;
	if (exec_list_node && exec_list_node->cmd)
	{
		cmd = ft_strdup(exec_list_node->cmd);
		if (ft_strcmp(cmd, "cd") || ft_strcmp(cmd, "export")
			|| ft_strcmp(cmd, "unset") || ft_strcmp(cmd, "exit"))
		{
			if (ft_strcmp(cmd, "export"))
				norminette_pleasing(exec_list_node, &bool);
			else
				bool = TRUE;
		}
		else
			bool = FALSE;
	}
	else
		bool = FALSE;
	free_chars(&cmd);
	return (bool);
}

t_bool	no_fork_solo_builtin(t_msh *msh)
{
	t_exec_list	*exec_list_node;

	if (msh && msh->exec_list)
	{
		exec_list_node = msh->exec_list;
		if (exec_list_node->pos_ppl != SOLO)
			return (FALSE);
		return (is_cmd_in_nfsolobuiltin_list(exec_list_node));
	}
	return (FALSE);
}

static void	do_nf_solo_builtin(t_msh *msh)
{
	if (msh && msh->exec_list && msh->exec_list->cmd)
	{
		if (ft_strcmp(msh->exec_list->cmd, "cd"))
			cd_builtin(msh, msh->exec_list);
		else if (ft_strcmp(msh->exec_list->cmd, "export"))
			export_builtin(msh, msh->exec_list);
		else if (ft_strcmp(msh->exec_list->cmd, "unset"))
			unset_builtin(msh, msh->exec_list);
		else if (ft_strcmp(msh->exec_list->cmd, "exit"))
			exit_builtin(msh, msh->exec_list);
	}
}

void	builtin_solo_without_fork(t_msh *msh)
{
	do_all_redir_solo_builtin(msh);
	if (!(msh->return_code))
		do_nf_solo_builtin(msh);
}
