/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:19:14 by amennad           #+#    #+#             */
/*   Updated: 2023/11/10 10:25:59 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_msh *msh)
{
	int				return_code;

	if (msh->lexer_list == NULL)
	{
		exit_new_line(msh);
		return ;
	}
	return_code = limit_is_valid(msh);
	if (return_code == 0)
		return_code = check_valid_next(msh);
	msh->return_code = return_code;
}
