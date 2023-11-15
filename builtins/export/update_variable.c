/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:49:10 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 10:49:21 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_variable(t_msh *msh, char *var_name, char *arg)
{
	char		*var_value;
	t_env_list	*env_list_node;

	if (msh && msh->env_list && var_name)
	{
		var_value = export_get_var_value(var_name, arg);
		env_list_node = msh->env_list;
		while (env_list_node)
		{
			if (ft_strcmp(env_list_node->name, var_name))
			{
				free_chars(&(env_list_node->value));
				env_list_node->value = ft_strdup(var_value);
				free_chars(&(var_value));
				return ;
			}
			env_list_node = env_list_node->next;
		}
		free_chars(&(var_value));
	}
}
