/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
/*   Updated: 2023/11/16 11:56:13 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_bool var_exist(t_msh *msh, char *var_name)
{
	t_env_list	*tmp;

	tmp = msh->env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var_name) == 0)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

void	generate_prompt(char *envp[])
{
	t_msh	*msh;
	char	*prompt;

	msh = new_msh();
	env_list_generate(msh, envp);
	build_user_for_prompt(msh);
	while (msh)
	{
		generate_msh_env(msh);
		msh->program_status = INTERACTIVE_STATUS;
		prompt = readline(msh->user);
		msh->program_status = EXECUTION_STATUS;
		//lexer_check(msh, msh->prompt);
		lexer_check(msh, prompt);
		free_chars(&prompt);
		if (msh->return_code == 0 && msh->lexer_list)
		{
			//print_debug_lexer_list(msh->lexer_list, "main lexer_list"); // à supprimer à terme
			parser(msh);
		}
		if (msh->return_code == 0 && msh->lexer_list)
		{
			expander(msh); // à réviser avec l'env propre à minishell
				print_debug_lexer_list(msh->lexer_list, "main lexer_list"); // à supprimer à terme
		// 		// print_exp_list_one_line(msh); // à supprimer à terme
				print_debug_exp_list(msh->exp_list, "main expander_list"); // à supprimer à terme

			if (expander_list_is_empty(msh->exp_list) == TRUE && (msh->exp_current_type == R_ORIGIN_REDIRECT || msh->exp_current_type == W_DEST_REDIRECT || msh->exp_current_type == WA_DEST_REDIRECT || msh->exp_current_type == LIMITER_HEREDOC))
			{
				//TODO VERIFIER QUE LA VAR QUE L'ON VEUT AFFICHER EXISTE ET EST VIDE ?? sinon juste c'est pas la bonne erreur et perso je m'en fiche
				exit_no_file_directory("");
			}
			else if (expander_list_is_empty(msh->exp_list) == TRUE )
			{
				exit_command_not_foud("");
			}
		}
		if (msh->return_code == 0 && msh->exp_list)
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
