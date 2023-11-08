/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_no_args_for_minishell_error_msg.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:15:22 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/08 15:15:39 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_no_args_for_minishell_error_msg(void)
{
	ft_putstr_fd("Error: minishell does not take any argument.\n", 2);
	ft_putstr_fd("In order to run minishell, please proceed that way :\n", 2);
	ft_putstr_fd("\n./minishell\n", 2);
	ft_putstr_fd("\nnothing more.\n", 2);
}
