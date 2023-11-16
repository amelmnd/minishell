/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_msh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:20:10 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 17:28:16 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_msh(t_msh *msh)
{
	msh->return_code = 0;
	msh->env_list = NULL;
	msh->msh_env = NULL;
	msh->user = NULL;
	// msh->prompt = NULL;
	msh->lexer_list = NULL;
	msh->exp_current_type = INIT_VALUE_EXP_CURRENT_TYPE;
	msh->exp_list = NULL;
	msh->exec_list = NULL;
	msh->exec = NULL;
}

t_msh *new_msh(void)
{
	t_msh	*new;

	new = NULL;
	new = (t_msh *)malloc(sizeof(t_msh));
	if (!new)
		return (NULL);
	init_msh(new);
	return (new);
}
