/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_duptwo_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:51:53 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/25 15:30:11 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_duptwo(t_ppx *ppx, int pretender, int to_replace)
{
	if (dup2(pretender, to_replace) == -1)
		errormsg_free_exit(ppx, "bash");
}
