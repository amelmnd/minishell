/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexer_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:07:48 by amennad           #+#    #+#             */
/*   Updated: 2023/11/25 00:17:37 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_lexer_cara(t_msh *msh, int *i, char c)
{
	int	return_code;

	return_code = msh->return_code;
	if (c == ' ' || c == '\t')
		return_code = is_blank(msh, msh->prompt, i);
	else if (c == 39)
		return_code = is_simple_quote(msh, msh->prompt, i);
	else if (c == 34)
		return_code = is_double_quote(msh, msh->prompt, i);
	else if (c == '|')
		return_code = is_pipe(msh, msh->prompt, i);
	else if (c == '>')
		return_code = is_right_bracket(msh, msh->prompt, i);
	else if (c == '<')
		return_code = is_left_bracket(msh, msh->prompt, i);
	else if (c == '$')
		return_code = is_dollar(msh, msh->prompt, i);
	else
		return_code = is_word(msh, msh->prompt, i);
	return (return_code);
}

int	lexer_create_list(t_msh *msh)
{
	int	i;
	int	return_code;
	int	len_prompt;

	i = 0;
	len_prompt = ft_strlen(msh->prompt);
	while (i < len_prompt)
	{
		return_code = is_lexer_cara(msh, &i, msh->prompt[i]);
		msh->return_code = return_code;
		if (return_code != 0)
			break ;
		i++;
	}
	return (return_code);
}
