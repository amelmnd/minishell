/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_from_env_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:30:23 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/24 15:49:37 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_the_first(t_msh *msh)
{
	t_env_list	*second;

	if (msh && msh->env_list)
	{
		second = msh->env_list->next;
		free_chars(&(msh->env_list->name));
		free_chars(&(msh->env_list->value));
		free(msh->env_list);
		msh->env_list = NULL;
		msh->env_list = second;
		msh->env_list->previous = NULL;
	}
}

static void	remove_the_last(t_msh *msh)
{
	t_env_list	*before_the_last;
	t_env_list	*last;

	if (msh && msh->env_list)
	{
		before_the_last = msh->env_list;
		while (before_the_last->next)
			before_the_last = before_the_last->next;
		last = before_the_last;
		before_the_last = before_the_last->previous;
		free_chars(&(last->name));
		free_chars(&(last->value));
		free(last);
		last = NULL;
		before_the_last->next = NULL;
	}
}

static void	remove_in_the_middle(t_msh *msh, char *var_name)
{
	t_env_list	*current;
	t_env_list	*previous;
	t_env_list	*next;

	if (msh && msh->env_list)
	{
		current = msh->env_list;
		while (current)
		{
			if (ft_strcmp(var_name, current->name))
			{
				previous = current->previous;
				next = current->next;
				free_chars(&(current->name));
				free_chars(&(current->value));
				free(current);
				current = NULL;
				current = previous;
				previous->next = next;
				next->previous = previous;
				return ;
			}
			current = current->next;
		}
	}
}

void	remove_from_env_list(t_msh *msh, char *var_name)
{
	t_env_list	*env_list;

	if (msh && msh->env_list)
	{
		env_list = msh->env_list;
		while (env_list)
		{
			if (ft_strcmp(var_name, env_list->name))
			{
				if (!(env_list->previous))
					remove_the_first(msh);
				else if (!(env_list->next))
					remove_the_last(msh);
				else
					remove_in_the_middle(msh, env_list->name);
				break ;
			}
			env_list = env_list->next;
		}
	}
}
