/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_msh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:46:01 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/20 18:06:46 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_msh(t_msh *msh)
{
	free_envlist(msh);
	free_ntcharss(&(msh->msh_env));
	free_chars(&(msh->user));
	free_chars(&(msh->prompt)); // à étudier si nécessaire
	free_lexer_list(msh);
	free_exp_list(msh);
	free_exec_list(msh);
	free_exec(msh);
	free(msh);
}
