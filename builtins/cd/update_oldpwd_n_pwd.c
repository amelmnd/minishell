/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_oldpwd_n_pwd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:25:23 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/20 10:29:23 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_list(t_msh *msh, char *name_var, char *new_value)
{
	t_env_list	*env_list_node;

	if (msh && msh->env_list && name_var)
	{
		env_list_node = msh->env_list;
		while (env_list_node)
		{
			if (ft_strcmp(env_list_node->name, name_var))
			{
				free_chars(&(env_list_node->value));
				env_list_node->value = NULL;
				env_list_node->value = ft_strdup(new_value);
				return ;
			}
			env_list_node = env_list_node->next;
		}
	}
}

void	update_oldpwd_n_pwd(t_msh *msh, char *oldpwd, char *pwd)
{
	if (msh && msh->env_list)
	{
		update_env_list(msh, "OLDPWD", oldpwd);
		update_env_list(msh, "PWD", pwd);
		msh->return_code = 0;
	}
}
