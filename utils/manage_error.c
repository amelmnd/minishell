/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:13:34 by amennad           #+#    #+#             */
/*   Updated: 2023/11/05 12:20:27 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO add here other error type

void	exit_synthax_error(t_msh *msh, char *str)
{
	msh->return_code = 2;
	rl_on_new_line();
	rl_replace_line("", 1);
	dprintf(2, "bash: syntax error near unexpected token '%s'\n", str);
	/*
	ft_putstr_fd("bash: syntax error near unexpected token ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	*/
}

void	exit_command_not_foud(char *str)
{
	rl_on_new_line();
	rl_replace_line("", 1);
	dprintf(2, "-bash: %s: command not found\n", str);
	/*
	ft_putstr_fd("-bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	*/
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*
 ces dprintf(2, "str") devront être remplacés par des ft_putstr_fd (déjà prêts en commentaire)
 dprintf n'étant pas une fonction autorisée
 d'autant plus que ces affichages auraient plus leur plus sur la sortie d'erreur
*/