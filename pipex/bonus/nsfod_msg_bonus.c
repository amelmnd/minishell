/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nsfod_msg_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:06:18 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/28 17:23:19 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	nsfod_msg(t_ppx *ppx, int num_cmd)
{
	write(2, "bash: ", 6);
	write(2, ppx->av[num_cmd], ft_strlen(ppx->av[num_cmd]));
	write(2, ": No such file or directory\n", 28);
}
