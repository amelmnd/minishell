/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexer_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:07:48 by amennad           #+#    #+#             */
/*   Updated: 2023/10/16 14:22:07 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void lexex_create_list(t_lexer_list *lexer_list, char *prompt)
{
	printf("prompt %s\n", prompt);
	lexer_list = ft_push(lexer_list, "tic et tac");
	printf("______NEW CALL______\n");
	lexer_list = ft_push(lexer_list, "tom et jerry");

	// int	i;
	// int	len;

	// i = 0;
	// len = ft_strlen(prompt);
	// while (i < len)
	// {
	// 	if (prompt[i] == 39)
	// 	{

	// 	}
	// 	i++;
	// }
}

/*
- <
- >
- <<
- >>
- |
- $?
*/
// int defined_lexer_type(char *prompt, int *i)
// {
// 	if
// }