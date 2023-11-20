/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
/*   Updated: 2023/11/20 19:09:12 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int print = 0;
// int		g_sigint = 0;

// void	sig_handler(int sig)
// {

// 	g_sigint = sig;
// 	signal(sig, SIG_IGN);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	printf("\n");
// 	rl_redisplay();
// 	signal(sig, sig_handler);
// }


void	generate_prompt(char *envp[])
{
	t_msh	*msh;

	msh = new_msh();

	msh = new_msh();
	env_list_generate(msh, envp);
	build_user_for_prompt(msh);
	while (msh)
	{
		if (print) {printf("generate_prompt(while) : début itération ; msh->return_code = %d\n", msh->return_code);}
		printf("msh->return_code = %d\n", msh->return_code);

		generate_msh_env(msh); // ne pas supprimer
		//assigne à msh->(char **)msh_env un char ** généré à partir de msh->env_list
		// qui est modifiée et conservée au fur et à mesure de cette boucle (generate_prompt)
		//print_charss(msh->msh_env);

		msh->program_status = INTERACTIVE_STATUS;
		ft_signal(msh);
		msh->prompt = readline(msh->user);
		if (msh->prompt == NULL && msh->program_status == INTERACTIVE_STATUS)
		{
			kill(0, SIGKILL); //kill tout y compris la VM
		}

		msh->program_status = EXECUTION_STATUS;
		ft_signal(msh);

		lexer_check(msh, msh->prompt);
		if (msh->return_code == 0 && msh->lexer_list)
		{
			parser(msh);
		}
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
