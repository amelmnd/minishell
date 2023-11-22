/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:31:10 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/22 21:54:52 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_msh *msh, t_exec_list *exec_list_node)
{
	t_env_list	*env_list;

	(void)exec_list_node;
	env_list = msh->env_list;
	while (env_list)
	{
		if (env_list->value)
			printf("%s=%s\n", env_list->name, env_list->value);
		else
			printf("%s=\n", env_list->name);
		env_list = env_list->next;
	}
}
