/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:09:30 by amennad           #+#    #+#             */
/*   Updated: 2023/11/25 05:22:20 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// clean between two generate_prompt's iterations 
// (thus, msh and msh->msh_env are not freed here)
void	clean_msh_list(t_msh *msh)
{
	free_lexer_list(msh);
	free_exp_list(msh);
	free_exec_list(msh);
	free_exec(msh);
	free_ntcharss(&(msh->msh_env));
	free_chars(&(msh->prompt));
	free_chars(&(msh->transexp));
	free_chars(&(msh->temp));
	free_exit(msh);
}

void	free_envlist(t_msh *msh)
{
	t_env_list	*current;
	t_env_list	*next;

	if (msh->env_list)
	{
		current = msh->env_list;
		while (current)
		{
			next = current->next;
			free_chars(&(current->name));
			free_chars(&(current->value));
			free(current);
			current = NULL;
			current = next;
		}
	}
}
