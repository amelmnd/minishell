/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:27:55 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/16 16:44:10 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(t_msh *msh, t_exec_list *exec_list_node)
{

	(void)exec_list_node;

	t_env_list	*env_list;

	env_list = msh->env_list;
	while (env_list)
	{
		if (ft_strcmp(env_list->name, "PWD"))
		{
			printf("%s\n", env_list->value);
			break ;
		}
		env_list = env_list->next;
	}
}