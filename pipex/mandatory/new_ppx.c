/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ppx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:01:15 by nstoutze          #+#    #+#             */
/*   Updated: 2023/06/29 19:49:23 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_ppx	*new_ppx(void)
{
	t_ppx	*new;

	new = (t_ppx *)malloc(sizeof(t_ppx));
	if (!new)
		errormsg_free_exit(new, "bash");
	return (new);
}
