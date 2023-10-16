/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexer_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:07:48 by amennad           #+#    #+#             */
/*   Updated: 2023/10/16 19:39:18 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int is_pipe(t_lexer_list *lexer_list, char *prompt, int *i, char c_current)
// {
// 	if (prompt[*i + 1] == '|')
// 	{
// 		exit_synthax_error(c_current);
// 		return (258);
// 	}
// 	else
// 	{
// 		lexer_list = ft_push(lexer_list, &c_current, PIPE);
// 	}
// }

int check_char(t_lexer_list *lexer_list, char *prompt, int *i)
{
	char current_cara;
	current_cara = prompt[*i];
	// printf("test %c\n", prompt[i + 1]);
	if (current_cara == '|')
	{
		if (prompt[*i + 1] == '|')
		{
			exit_synthax_error(current_cara);
			return (258);
		}
		else
		{
			lexer_list = ft_push(lexer_list, &current_cara, PIPE);
		}
	}
	return (0);
}

int lexex_create_list(t_lexer_list *lexer_list, char *prompt)
{

	int i;
	int len;
	int return_code;

	i = 0;
	len = ft_strlen(prompt);
	while (i < len)
	{
		return_code = check_char(lexer_list, prompt, &i);
		if (return_code)
			break;
		i++;
	}
	return (return_code);
}

/*
- <
- >
- <<
- >>
- |
- $?
*/
