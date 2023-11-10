/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:26:16 by amennad           #+#    #+#             */
/*   Updated: 2023/11/10 17:22:14 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_msh *msh)
{
	// msh->exp_current_type = WORD_EXPANDED;
	check_var_value(msh);
	create_expander_list(msh);
	if (!msh->exp_list)
	{
		exit_new_line(msh);
	}
}
