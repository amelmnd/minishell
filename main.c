/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
/*   Updated: 2023/11/05 12:41:18 by nstoutze         ###   ########.fr       */
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
	init_msh(msh);
	env_list_generate(msh, envp);
	// print_env_list(msh->env_list);
	user = getenv("USER");
	user = ft_strjoin(user, " $> ");
	while (1)
	{
		prompt = readline(user);
		lexer_check(msh, prompt);

		if (msh->return_code == 0 && msh->lexer_list)
		{
			// print_debug_lexer_list(msh->lexer_list, "main lexer_list");
			parser(msh);
		}
		if (msh->return_code == 0 && msh->lexer_list)
		{
			expander(msh);
			if (msh->exp_list)
			{
				//print_exp_list_one_line(msh);
				//print_debug_exp_list(msh->exp_list, "main expander_list");
			}
		}
		build_exec_list(msh);
		//print_exec_list(msh);
		
		execution(msh, envp);


		clean_msh_list(msh);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	if (argc != 1)
	{
		//show_no_args_for_minishell_msg();
		return (0);
	}
	generate_prompt(envp);
	return (0);
}

/*
ls|cat ne fonctionne pas :
	le pipe n'est pas pris en compte
	l'expander sort juste deux mots d'affilée

Les commandes suivantes :

- première commande : ls > lol
spardaspirit $> ls > lol
(WORD_EXPANDED)ls (W_DEST_REDIRECT)lol 
spardaspirit $> Segmentation fault (core dumped)
// le Segmentation fault (core dumped) s'affiche tout seul dans le prompt,
// je ne l'ai pas saisi

- deuxième commande : echo coucou > mdr
(même erreur)

provoquent une segfault au moment du réaffichage du prompt
valgrind indique une anomalie du ft_strlen (ah ouais, à ce point ???)
cela semble être uniquement le cas des lignes ne contenant aucun pipe
dès qu'il y au moins un pipe, la segfault n'apparait plus
*/