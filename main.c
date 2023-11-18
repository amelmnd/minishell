/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
/*   Updated: 2023/11/18 21:26:32 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int print = 0;

void	generate_prompt(char *envp[])
{
	t_msh	*msh;

	msh = new_msh();
	env_list_generate(msh, envp);
	build_user_for_prompt(msh);
	while (42 && msh)
	{
		if (print) {printf("generate_prompt(while) : début itération ; msh->return_code = %d\n", msh->return_code);}

		generate_msh_env(msh);

		msh->program_status = INTERACTIVE_STATUS;
		msh->prompt = readline(msh->user);
		msh->program_status = EXECUTION_STATUS;
		lexer_check(msh, msh->prompt);
		if (msh->return_code == 0 && msh->lexer_list)
		{
			//print_debug_lexer_list(msh->lexer_list, "main lexer_list"); // à supprimer à terme
			parser(msh);
		}
		if (msh->return_code == 0 && msh->lexer_list)
		{
			expander(msh); // à réviser avec l'env propre à minishell
			/*
			if (msh->exp_list)
			{
				//print_exp_list_one_line(msh); // à supprimer à terme
				//print_debug_exp_list(msh->exp_list, "main expander_list"); // à supprimer à terme
			}
			*/
		}
		if (msh->return_code == 0 && msh->lexer_list)
		{
			build_exec_list(msh);
			execution(msh);
		}
		clean_msh_list(msh);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	if (argc == 1)
		generate_prompt(envp);
	else
		show_no_args_for_minishell_error_msg();
	return (0);
}

/*
il faudra penser à retirer gnl lorsqu'il ne sera plus utilisé
(ou pas, comme beaucoup de fichiers de la libft non utilisés dans minishell)

fsanitize change les msh->return_code

rectifier les messages d'erreur avec la recherche "minishell:"

Chasser tous les perror (pour les remplacer par des ft_putstr_fd(2))

sécuriser tous les appels système type : pipe, fork, close, dup2, dup, etc...
*/