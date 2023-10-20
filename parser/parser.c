/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:19:14 by amennad           #+#    #+#             */
/*   Updated: 2023/10/20 19:36:27 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_msh *msh)
{
	int				return_code;

	if (msh->lexer_list == NULL)
	{
		exit_new_line();
		return ;
	}
	return_code = limit_is_valid(msh);
	return_code = check_valid_next(msh);
	msh->return_code = return_code;
}
