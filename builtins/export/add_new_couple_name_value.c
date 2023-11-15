/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_couple_name_value.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:47:39 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 10:47:53 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_couple_name_value(t_msh *msh, char *var_name, char *arg)
{
	t_env_list	*new_env_list_node;
	t_env_list	*last_env_list_node;

	new_env_list_node = NULL;
	last_env_list_node = NULL;
	if (msh && msh->env_list && var_name)
	{
		new_env_list_node = new_env_list();
		new_env_list_node->name = ft_strdup(var_name);
		if (is_chr_in_str(arg, '='))
			new_env_list_node->value = export_get_var_value(var_name, arg);
		last_env_list_node = msh->env_list;
		while (last_env_list_node->next)
			last_env_list_node = last_env_list_node->next;
		last_env_list_node->next = new_env_list_node;
		new_env_list_node->previous = last_env_list_node;
	}
}
