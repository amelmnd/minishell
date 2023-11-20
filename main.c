/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
/*   Updated: 2023/11/20 19:36:38 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	generate_prompt(char *envp[])
{
	t_msh	*msh;

	msh = new_msh();
	env_list_generate(msh, envp);
	build_user_for_prompt(msh);
	while (msh)
	{
		generate_msh_env(msh);
		msh->program_status = INTERACTIVE_STATUS;
		msh->prompt = readline(msh->user);
		msh->program_status = EXECUTION_STATUS;

		lexer_check(msh, msh->prompt);
		if (msh->return_code == 0 && msh->lexer_list)
		{
			parser(msh);
		}
				print_debug_lexer_list(msh->lexer_list, "main lexer_list"); // à supprimer à terme
		if (msh->return_code == 0 && msh->lexer_list)
		{
			expander(msh); // à réviser avec l'env propre à minishell

			if (msh->exp_list)
			{
				print_debug_lexer_list(msh->lexer_list, "main lexer_list"); // à supprimer à terme
				// print_exp_list_one_line(msh); // à supprimer à terme
				print_debug_exp_list(msh->exp_list, "main expander_list"); // à supprimer à terme
			}
		}
		if (msh->return_code == 0 && msh->lexer_list) // TODO c'est pas plutot expander liste qu'il faut tester ?
		{
			build_exec_list(msh);
			execution(msh);
		}
		clean_msh_list(msh);
	}
	clear_history ();
	//avec le break ci-dessous : à réactiver tant que les signaux n'ont pas été
	//gérés pour tester les leaks
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
