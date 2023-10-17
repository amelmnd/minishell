/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:13:34 by amennad           #+#    #+#             */
/*   Updated: 2023/10/17 17:41:49 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO add here other error type

void	exit_synthax_error(t_msh *msh, char cara)
{
	clean_msh(msh);
	rl_on_new_line();
	rl_replace_line("", 1);
	printf("bash: erreur de syntaxe près du symbole inattendu « %c »\n", cara);
}
