/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:34:33 by amennad           #+#    #+#             */
/*   Updated: 2023/10/16 19:40:25 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_new_line(void)
{
	rl_on_new_line();
}

void	exit_synthax_error(char cara)
{
	rl_on_new_line();
    rl_replace_line("", 1);
	printf("bash: erreur de syntaxe près du symbole inattendu « %c »\n", cara);
    // rl_redisplay();
}