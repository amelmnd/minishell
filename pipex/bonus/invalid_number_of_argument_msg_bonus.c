/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_number_of_argument_msg_bonus.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:32:28 by nstoutze          #+#    #+#             */
/*   Updated: 2023/07/03 20:19:17 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	invalid_number_of_argument_msg_bonus(void)
{
	write(2, "Error : at least four arguments needed.\n", 40);
	write(2, "Example : ./pipex_bonus infile cmd1 cmd2 cmd3", 45);
	write(2, "... outfile\nOr, with a here_doc, at least five :\n", 49);
	write(2, "./pipex_bonus here_doc DELIMITER cmd1", 37);
	write(2, " cmd2 cmd3 ... cmdn outfile\n", 28);
}
