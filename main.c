/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
/*   Updated: 2023/10/16 12:36:13 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	generate_prompt(void)
{
	char			*user;
	char			*prompt;
	t_lexer_list	*lexer_list;

	lexer_list = NULL;

	user = getenv("USER");
	user = ft_strjoin(user, " $> ");
	while (1)
	{
		prompt = readline(user);
		lexer_check(lexer_list, prompt);
	}
}

int	main(void)
{
	generate_prompt();
	return (0);
}
