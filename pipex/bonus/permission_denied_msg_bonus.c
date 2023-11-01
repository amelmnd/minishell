/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission_denied_msg_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:07:16 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/28 17:08:44 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	permission_denied_msg(t_ppx *ppx, int n)
{
	write(2, "bash: ", 6);
	write(2, ppx->av[n], ft_strlen(ppx->av[n]));
	write(2, ": Permission denied\n", 20);
}
