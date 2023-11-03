/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsfod_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:06:18 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 19:49:28 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	nsfod_msg(t_ppx *ppx, int num_cmd)
{
	write(2, "bash: ", 6);
	write(2, ppx->av[num_cmd], ft_strlen(ppx->av[num_cmd]));
	write(2, ": No such file or directory\n", 28);
}
