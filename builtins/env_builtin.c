/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:31:10 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/18 21:16:30 by nstoutze         ###   ########.fr       */
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
		printf("%s=\"%s\"\n", env_list->name, env_list->value);
		env_list = env_list->next;
	}
}
