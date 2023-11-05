/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexer_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:07:48 by amennad           #+#    #+#             */
/*   Updated: 2023/11/05 16:08:16 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_lexer_cara(t_msh *msh, char *prompt, int *i, char c)
{
	int	return_code;

	return_code = 0;
	if (c == ' ' || c == '\t')
		return_code = is_blank(msh, prompt, i);
	else if (c == 39)
		return_code = is_simple_quote(msh, prompt, i);
	else if (c == 34)
		return_code = is_double_quote(msh, prompt, i);
	else if (c == '|')
		return_code = is_pipe(msh, prompt, i);
	else if (c == '>')
		return_code = is_right_bracket(msh, prompt, i);
	else if (c == '<')
		return_code = is_left_bracket(msh, prompt, i);
	else if (c == '$')
		return_code = is_dollar(msh, prompt, i);
	else
		return_code = is_word(msh, prompt, i);
	return (return_code);
}

int	lexer_create_list(t_msh *msh, char *prompt)
{
	int	i;
	int	return_code;

	i = 0;
	while (i < ft_strlen(prompt))
	{
		return_code = is_lexer_cara(msh, prompt, &i, prompt[i]);
		msh->return_code = return_code;
		if (return_code != 0)
		{
			break ;
		}
		i++;
	}
	return (return_code);
}
