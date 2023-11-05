/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
/*   Updated: 2023/11/05 16:16:38 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int print = 1;

void	generate_prompt(char *envp[])
{
	if (print) {dprintf(2,"generate_prompt : Entrée\n");}
	t_msh	*msh;
	char	*user;
	char	*prompt;

	msh = (t_msh *)malloc(sizeof(t_msh));
	if (!msh)
		return ;
	if (print) {dprintf(2,"generate_prompt : 1 ; msh malloc\n");}
	init_msh(msh);
	if (print) {dprintf(2,"generate_prompt : 2 ; msh initialized\n");}
	env_list_generate(msh, envp);
	if (print) {dprintf(2,"generate_prompt : 3 ; env_list generated\n");}
	// print_env_list(msh->env_list);
	user = getenv("USER");
	if (print) {dprintf(2,"generate_prompt : 4 ; user assigned with getenv function\n");}
	user = ft_strjoin(user, " $> ");
	if (print) {dprintf(2,"generate_prompt : 5 ; user append with $>\n");}
	while (42)
	{
		if (print) {dprintf(2,"generate_prompt(while) : 6 ; début nouvelle itération\n");}

		if (print) {dprintf(2,"generate_prompt(while) : 6,1 ; sleep 2 imminent\n");}
		sleep(2);
		if (print) {dprintf(2,"generate_prompt(while) : 6,2 ; sleep 2 DONE\n");}
		
		prompt = readline(user);
		if (print) {dprintf(2,"generate_prompt(while) : 7 ; prompt assigned with readline\n");}
		/*
		if (print) {dprintf(2,"generate_prompt(while) : 6,3 ; ft_putstr_fd(user, 2) imminent\n");}
		ft_putstr_fd(user, 2);
		prompt = get_next_line(0);
		if (print) {dprintf(2,"generate_prompt(while) : 7 ; prompt assigned with gnl\n");}
		*/
	
		lexer_check(msh, prompt);
		if (print) {dprintf(2,"generate_prompt(while) : 8 ; lexer check DONE\n");}

		if (print) {dprintf(2,"generate_prompt(while) : 9 ; premier if du while imminent\n");}
		if (msh->return_code == 0 && msh->lexer_list)
		{
			if (print) {dprintf(2,"generate_prompt(while) : 9.1 ; entrée dans le premier if du while\n");}
			// print_debug_lexer_list(msh->lexer_list, "main lexer_list");
			parser(msh);
			if (print) {dprintf(2,"generate_prompt(while) : 9.2 ; parser DONE\n");}
		}
		if (print) {dprintf(2,"generate_prompt(while) : 10 ; deuxieme if du while imminent\n");}
		if (msh->return_code == 0 && msh->lexer_list)
		{
			if (print) {dprintf(2,"generate_prompt(while) : 10.1 ; entrée deuxieme if du while\n");}
			expander(msh);
			if (print) {dprintf(2,"generate_prompt(while) : 10.2 ; expander DONE\n");}

			/*
			if (msh->exp_list)
			{
				//print_exp_list_one_line(msh);
				//print_debug_exp_list(msh->exp_list, "main expander_list");
			}
			*/
		}
		if (print) {dprintf(2,"generate_prompt(while) : 11 ; build_exec_list imminent\n");}
		build_exec_list(msh);
		if (print) {dprintf(2,"generate_prompt(while) : 12 ; build_exec_list DONE\n");}
		//print_exec_list(msh);
		
		if (print) {dprintf(2,"generate_prompt(while) : 13 ; execution imminent\n");}
		execution(msh, envp);
		if (print) {dprintf(2,"generate_prompt(while) : 14 ; execution DONE\n");}

		if (print) {dprintf(2,"generate_prompt(while) : 15 ; clean_msh_list imminent\n");}
		clean_msh_list(msh);
		if (print) {dprintf(2,"generate_prompt(while) : 16 ; clean_msh_list DONE\n");}

		if (print) {dprintf(2,"generate_prompt(while) : 17 ; free_chars(&prompt) imminent\n");}
		free_chars(&prompt);
		if (print) {dprintf(2,"generate_prompt(while) : 18 ; free_chars(&prompt) DONE\n");}

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