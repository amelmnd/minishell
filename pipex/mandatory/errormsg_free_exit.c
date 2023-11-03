/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errormsg_free_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:28:30 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 19:46:36 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	errormsg_free_exit(t_ppx *ppx, char *errormsg)
{
	if (!ft_strlen(ppx->av[ppx->num_cmd]))
		perror(errormsg);
	free_ppx(ppx);
	exit(EXIT_FAILURE);
}
	//system("leaks pipex_bonus");
