/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_not_found_msg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:55:31 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 19:46:29 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	cmd_not_found_msg(t_ppx *ppx)
{
	write(2, "bash: ", 6);
	write(2, ppx->av[ppx->num_cmd], ft_strlen(ppx->av[ppx->num_cmd]));
	write(2, ": command not found\n", 20);
	exit(EXIT_FAILURE);
}
