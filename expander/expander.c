/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:26:16 by amennad           #+#    #+#             */
/*   Updated: 2023/10/28 16:34:02 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_msh *msh)
{
	msh->exp_current_type = WORD_EXPANDED;
	check_var_value(msh);
	create_expander_list(msh);
}
