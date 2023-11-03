/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:13:34 by amennad           #+#    #+#             */
/*   Updated: 2023/11/03 14:11:38 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO add here other error type

void	exit_synthax_error(t_msh *msh, char *str)
{
	msh->return_code = 2;
	rl_on_new_line();
	rl_replace_line("", 1);
	printf("bash: syntax error near unexpected token '%s'\n", str);
}

void	exit_command_not_foud(char *str)
{
	rl_on_new_line();
	rl_replace_line("", 1);
	printf("-bash: %s: command not found\n", str);
}
