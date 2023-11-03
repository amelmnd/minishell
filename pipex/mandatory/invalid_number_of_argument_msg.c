/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_number_of_argument_msg.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:32:28 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 19:58:06 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	invalid_number_of_argument_msg(void)
{
	write(2, "Error : exactly four arguments needed.\n", 39);
	write(2, "Example : ./pipex_bonus infile cmd1 cmd2 outfile\n", 49);
}
