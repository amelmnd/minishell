/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:09:57 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 11:00:18 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_builtin(t_msh *msh, t_exec_list *exec_list_node)
{
	if (msh && exec_list_node)
	{
		if (exec_list_node->nb_words == 1)
			export_without_args(msh);
		else
			export_with_args(msh, exec_list_node);
	}
}
