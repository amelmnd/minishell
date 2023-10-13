/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:09:55 by amennad           #+#    #+#             */
/*   Updated: 2023/10/13 12:12:43 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_check(t_lexer_list **lexer_list, char *prompt)
{
	int			i;
	enum e_bool	is_empty;

	i = 0;
	is_empty = TRUE;
	*lexer_list = NULL;

	while (prompt[i] != '\0')
	{
		if (prompt[i] != ' ')
		{
			is_empty = FALSE;
		}
		i++;
	}
	if (is_empty == TRUE)
		rl_on_new_line();
}
