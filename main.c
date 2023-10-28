/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
/*   Updated: 2023/10/28 16:12:03 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	generate_prompt(char *envp[])
{
	t_msh	*msh;
	char	*user;
	char	*prompt;

	msh = (t_msh *)malloc(sizeof(t_msh));
	if (!msh)
		return ;
	env_list_generate(msh, envp);
	user = getenv("USER");
	user = ft_strjoin(user, " $> ");
	while (1)
	{
		prompt = readline(user);
		lexer_check(msh, prompt);
		if (msh->return_code == 0 && msh->lexer_list)
			parser(msh);
		if (msh->return_code == 0)
			expander(msh);
		clean_msh_list(msh);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	generate_prompt(envp);
	return (0);
}
