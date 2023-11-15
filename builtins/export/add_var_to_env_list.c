/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var_to_env_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:51:55 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 10:52:06 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	var_already_exists(t_msh *msh, char *var_name)
{
	t_env_list	*env_list_node;

	if (msh && msh->env_list && var_name)
	{
		env_list_node = msh->env_list;
		while (env_list_node)
		{
			if (ft_strcmp(env_list_node->name, var_name))
				return (TRUE);
			env_list_node = env_list_node->next;
		}
	}
	return (FALSE);
}

void	add_var_to_env_list(t_msh *msh, char *var_name, char *arg)
{
	if (msh && msh->env_list && var_name && arg)
	{
		if (var_already_exists(msh, var_name))
			update_variable(msh, var_name, arg);
		else
			add_new_couple_name_value(msh, var_name, arg);
	}
}
