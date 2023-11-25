/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_synthax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 04:38:53 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/25 04:39:03 by nstoutze         ###   ########.fr       */
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
