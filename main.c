/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
/*   Updated: 2023/11/15 09:08:30 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int print = 1;

void	generate_prompt(char *envp[])
{
	t_msh	*msh;

	msh = new_msh();
	env_list_generate(msh, envp);
	build_user_for_prompt(msh);
	while (42 && msh)
	{
		if (print) {printf("generate_prompt(while) : début itération ; msh->return_code = %d\n", msh->return_code);}

		generate_msh_env(msh); // ne pas supprimer
		//assigne à msh->(char **)msh_env un char ** généré à partir de msh->env_list
		// qui est modifiée et conservée au fur et à mesure de cette boucle (generate_prompt)
		//print_charss(msh->msh_env);

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
		//break ;
	}
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

/*
il est possible d'export des variables sans valeur
export les affiche
env ne les affiche pas

'export lol' ajoute une variable sans valeur
'export lol=' ajoute une variable avec valeur

la variable d'environnement _ est affichée par env, mais pas part export

au moment de l'export : s'il y a un =, une chaine vide est associée au nom
la variable est affichée par export tel que : nom_var=""
la variable est affichée par env tel que : nom_var=

fsanitize change les msh->return_code
*/