/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ppx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:35:44 by nstoutze          #+#    #+#             */
/*   Updated: 2023/07/02 18:34:31 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_ppx(t_ppx *ppx)
{
	free_charss(&(ppx->av));
	free_charss(&(ppx->envp));
	free_charss(&(ppx->paths_from_path));
	free_chars(&(ppx->path_from_envp));
	free_chars(&(ppx->slash_and_cmd));
	free_charss(&(ppx->args));
	free(ppx);
	unlink(".temp");
}
