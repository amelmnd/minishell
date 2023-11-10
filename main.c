/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
/*   Updated: 2023/11/10 17:23:54 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int print = 0;



void	generate_prompt(char *envp[])
{
	t_msh	*msh;

	msh = new_msh();
	if (!msh)
		return ;
	env_list_generate(msh, envp);
	build_user_for_prompt(msh);
	while (42)
	{
		if (print) {printf("generate_prompt(while) : début itération ; msh->return_code = %d\n", msh->return_code);}
		//msh->return_code est conservé d'une itération à la suivante (ce que l'on <veut)
		// une instruction dans la suite de la boucle réassigne la valeur à 0 avant l'expander
		// ce qui empêche de pouvoir l'afficher avec un echo $? par exemple

		//generate_msh_env(msh); // ne pas supprimer
		//assigne à msh->(char **)msh_env un char ** généré à partir de msh->env_list
		// qui est modifiée et conservée au fur et à mesure de cette boucle (generate_prompt)

		msh->prompt = readline(msh->user);
		lexer_check(msh, msh->prompt);
		if (msh->return_code == 0 && msh->lexer_list)
		{
			// print_debug_lexer_list(msh->lexer_list, "main lexer_list"); // à supprimer à terme
			parser(msh);
		}
		if (msh->return_code == 0 && msh->lexer_list)
		{
			expander(msh); // à réviser avec l'env propre à minishell
			// print_debug_lexer_list(msh->lexer_list, "main parser_lexer_list"); // delete => see var value
			// print_debug_exp_list(msh->exp_list, "main expander_list"); // à supprimer à terme
		}
		dev_clean_msh_list(msh);
		// if (msh->return_code == 0 && msh->lexer_list)
		// {
		// 	build_exec_list(msh);
		// 	execution(msh, envp);
		// }
		// clean_msh_list(msh);
		// break ;
	}
	//avec le break ci-dessous : à réactiver tant que les signaux n'ont pas été
	//gérés pour tester les leaks
	/*
	free_envlist(msh);
	free(msh);
	msh = NULL;
	*/
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
