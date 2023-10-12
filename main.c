/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
/*   Updated: 2023/10/12 15:44:17 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void generate_prompt(void)
{
	char *user;
	char *prompt;

	user = getenv("USER");
	user = ft_strjoin(user, " $> ");
	while (1)
	{
		prompt = readline(user);
		printf("%s\n", prompt);
	}
}

int	main(void)
{
	generate_prompt();
	return (0);
}
