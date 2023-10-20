/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
/*   Updated: 2023/10/20 15:13:20 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	generate_prompt(void)
{
	t_msh	*msh;
	char	*user;
	char	*prompt;

	msh = (t_msh *)malloc(sizeof(t_msh));
	user = getenv("USER");
	user = ft_strjoin(user, " $> ");
	if (!msh)
		return ;
	while (1)
	{
		prompt = readline(user);
		lexer_check(msh, prompt);
		parser(msh);
		print_debug_list(msh->lexer_list, "main");
		clean_msh(msh);
	}
}

int	main(void)
{
	generate_prompt();
	return (0);
}
