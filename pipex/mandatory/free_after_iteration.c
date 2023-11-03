/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_after_iteration.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:05:43 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/20 15:38:19 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_after_iteration(t_ppx *ppx)
{
	free_chars(&(ppx->slash_and_cmd));
	free_chars(&(ppx->abs_path_cmd));
	free_charss(&(ppx->args));
}
