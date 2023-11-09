/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_hd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:14:08 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/07 23:14:20 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hd	*new_hd(void)
{
	t_hd	*new;

	new = NULL;
	new = (t_hd *)malloc(sizeof(t_hd));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->str = NULL;
	return (new);
}
