/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_generate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:04:31 by amennad           #+#    #+#             */
/*   Updated: 2023/11/25 05:25:47 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_first_env_list_node(t_msh *msh, char *var_n_value)
{
	t_env_list	*first_env_list_node;

	first_env_list_node = msh->env_list;
	feed_env_list_node(first_env_list_node, var_n_value);
}

static void	append_new_fed_list_node(t_msh *msh, char *var_n_value)
{
	t_env_list	*last_env_list_node;
	t_env_list	*new_env_list_node;

	last_env_list_node = msh->env_list;
	new_env_list_node = new_env_list();
	while (last_env_list_node->next)
		last_env_list_node = last_env_list_node->next;
	last_env_list_node->next = new_env_list_node;
	new_env_list_node->previous = last_env_list_node;
	feed_env_list_node(new_env_list_node, var_n_value);
}

t_env_list	*new_env_list(void)
{
	t_env_list	*new;

	new = NULL;
	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	new->name = NULL;
	new->next = NULL;
	new->previous = NULL;
	new->value = NULL;
	return (new);
}

void	env_list_generate(t_msh *msh, char *envp[])
{
	int	i;

	i = -1;
	if (msh)
	{
		if (envp)
			msh->env_list = new_env_list();
		while (envp && envp[++i])
		{
			if (!i)
				fill_first_env_list_node(msh, envp[i]);
			else
				append_new_fed_list_node(msh, envp[i]);
		}
	}
}
