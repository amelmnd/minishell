/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_slash_and_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:21:49 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/20 15:38:01 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	build_slash_and_cmd(t_ppx *ppx)
{
	char	*slash_and_cmd;

	slash_and_cmd = NULL;
	ppx->args = ft_split(ppx, ppx->av[ppx->num_cmd], ' ');
	slash_and_cmd = ft_strdup(ppx, ppx->args[0]);
	ppx->slash_and_cmd = ft_strjoin(ppx, "/", slash_and_cmd);
	free_chars(&slash_and_cmd);
}
