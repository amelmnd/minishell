/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:13:34 by amennad           #+#    #+#             */
/*   Updated: 2023/11/24 00:13:10 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_synthax_error(t_msh *msh, char *str)
{
	msh->return_code = 2;
	rl_on_new_line();
	rl_replace_line("", 1);
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	exit_command_not_foud(char *str)
{
	rl_on_new_line();
	rl_replace_line("", 1);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	exit_no_file_directory(char *str)
{
	rl_on_new_line();
	rl_replace_line("", 1);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	ambiguous_redirect_errmsg(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

void	is_a_directory_errmsg(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": Is a directory\n", 2);
}
