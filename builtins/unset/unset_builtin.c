/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:29:02 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/24 16:06:36 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	exists_in_mshenv(t_msh *msh, char *var_name)
{
	t_bool		ret;
	t_env_list	*env_list;

	ret = FALSE;
	if (msh && msh->env_list)
	{
		env_list = msh->env_list;
		while (env_list)
		{
			if (ft_strcmp(var_name, env_list->name))
				ret = TRUE;
			env_list = env_list->next;
		}
	}
	return (ret);
}

void	unset_builtin(t_msh *msh, t_exec_list *exec_list_node)
{
	int	i;

	if (msh && exec_list_node->nb_words > 1)
	{
		i = 0;
		while (++i < exec_list_node->nb_words)
		{
			if (exists_in_mshenv(msh, exec_list_node->args_array[i]))
				remove_from_env_list(msh, exec_list_node->args_array[i]);
		}
	}
}
