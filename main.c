/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2023/10/12 22:53:18 by nstoutze         ###   ########.fr       */
=======
/*   Updated: 2023/11/02 18:37:11 by nstoutze         ###   ########.fr       */
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
		printf("%s\n", prompt);
=======
		lexer_check(msh, prompt);
		print_debug_lexer_list(msh->lexer_list, "main lexer_list");
		if (msh->return_code == 0 && msh->lexer_list)
			parser(msh);
		printf("msh->return_code = %d\n", msh->return_code);
		if (msh->return_code == 0 && msh->lexer_list)
        {
            expander(msh);
            if (msh->exp_list)
                print_debug_exp_list(msh->exp_list, "main expander_list");
        }
		clean_msh_list(msh);
>>>>>>> Stashed changes
	}
}

/*
int	main(void)
{
	generate_prompt();
	return (0);
}
*/