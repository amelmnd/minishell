/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ppx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:35:44 by nstoutze          #+#    #+#             */
/*   Updated: 2023/07/02 18:34:38 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_hdc(t_ppx *ppx)
{
	t_hdc	*hdc;
	t_hdc	*next;

	hdc = ppx->hdc;
	while (hdc)
	{
		next = hdc->next;
		free_chars(&(hdc->s));
		free(hdc);
		hdc = next;
	}
}

void	free_ppx(t_ppx *ppx)
{
	free_charss(&(ppx->av));
	free_charss(&(ppx->envp));
	free_charss(&(ppx->paths_from_path));
	free_chars(&(ppx->path_from_envp));
	free_chars(&(ppx->slash_and_cmd));
	free_charss(&(ppx->args));
	free_chars(&(ppx->delimiter));
	if (ppx->hdc)
		free_hdc(ppx);
	free(ppx);
	unlink(".temp");
}
