/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:07:48 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 19:47:22 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_execve(t_ppx *ppx)
{
	if (execve(ppx->abs_path_cmd, ppx->args, ppx->envp) == -1)
		errormsg_free_exit(ppx, "bash");
}
