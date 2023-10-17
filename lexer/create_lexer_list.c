/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexer_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:07:48 by amennad           #+#    #+#             */
/*   Updated: 2023/10/17 11:16:06 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
- |
- >
- <
- <<
- >>
- $?
*/

int is_pipe(t_lexer_list **lexer_list, char *prompt, int *i)
{
	if (*i == 0 || prompt[*i + 1] == '|')
	{
		// TODO CLEAR LIST
		exit_synthax_error('|');
		return (258);
	}
	else
		*lexer_list = ft_push(lexer_list, "|", PIPE);
	return (0);
}

int lexer_create_list(t_lexer_list **lexer_list, char *prompt)
{
	int i;
	int return_code;

	i = 0;
	return_code = 0;
	while (i < ft_strlen(prompt))
	{
		if (prompt[i] == '|')
			return_code = is_pipe(lexer_list, prompt, &i);
		if (return_code != 0)
			break;
		i++;
	}
	return (return_code);
}
