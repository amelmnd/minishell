/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_element.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:15:44 by amennad           #+#    #+#             */
/*   Updated: 2023/11/24 17:24:10 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	that_is_wold(t_msh *msh, t_lexer_list *tmp, char **str, int *not_exist_var)
{
	int	str_check;

	str_check = check_word(msh, tmp, str);
	if (str_check == 0 || *not_exist_var == 2)
		all_in_str(str, tmp->str);
	else if (str_check == 1)
		return (1);
	return (0);
}

void	is_special_var(t_msh *msh, t_lexer_list *tmp, char **str)
{
	if (msh->exp_current_type == R_ORIGIN_REDIRECT
		|| msh->exp_current_type == W_DEST_REDIRECT
		|| msh->exp_current_type == WA_DEST_REDIRECT)
		all_in_str(str, tmp->str);
	else
		all_in_str(str, "");
}
