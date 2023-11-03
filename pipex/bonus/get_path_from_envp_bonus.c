/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_from_envp_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:22:34 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/28 15:43:17 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	get_path_from_envp(t_ppx *ppx)
{
	char	*temp;

	ppx->i = 0;
	temp = NULL;
	while (ppx->envp[ppx->i] && ft_strncmp(ppx->envp[ppx->i], "PATH=", 5))
		ppx->i++;
	if (!(ppx->envp[ppx->i]))
		ppx->path_defined = 0;
	else if (!ft_strncmp(ppx->envp[ppx->i], "PATH=", 5))
	{
		temp = ft_strdup(ppx, ppx->envp[ppx->i]);
		ppx->path_from_envp = ft_substr(ppx, temp, 5, ft_strlen(temp));
		ppx->path_defined = 1;
	}
	else
		ppx->path_defined = 0;
	free_chars(&temp);
}
