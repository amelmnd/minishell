/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_user_for_prompt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:50:08 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/08 19:30:37 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*msh_getenv(t_msh *msh, char *var_name)
{
	t_env_list	*env_list;
	char		*var_value;
	
	env_list = NULL;
	var_value = NULL;
	if (msh && msh->env_list && var_name)
	{
		env_list = msh->env_list;
		while (env_list)
		{
			if (ft_strcmp(env_list->name, var_name))
				var_value = ft_strdup(env_list->value);
			env_list = env_list->next;
		}
	}
	return (var_value);
}

void	build_user_for_prompt(t_msh *msh)
{
	char	*proto_user;

	proto_user = NULL;
	if (msh && msh->env_list)
	{
		proto_user = msh_getenv(msh, "USER");
		msh->user = ft_strjoin(proto_user, " $> ");
		free_chars(&(proto_user));
	}
}
