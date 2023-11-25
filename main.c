/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
/*   Updated: 2023/11/25 03:09:34 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_bool var_exist(t_msh *msh, char *var_name)
{
	// on peut déplacer cette fonction ailleurs ?
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

	msh = new_msh();
	env_list_generate(msh, envp);
	build_user_for_prompt(msh);
	while (msh)
	{
		msh->stored_return_code = msh->return_code;
		msh->return_code = 0;
		generate_msh_env(msh);
		msh->program_status = INTERACTIVE_STATUS;
		ft_signal(msh);
		msh->prompt = readline(msh->user);
		if (msh->prompt == NULL && msh->program_status == INTERACTIVE_STATUS)
			kill(0, SIGKILL);
		msh->program_status = EXECUTION_STATUS;
		ft_signal(msh);
		//lexer_check(msh, msh->prompt);
		//prompt = ft_strdup(msh->prompt);
		lexer_check(msh);
		if (!(msh->return_code) && msh->lexer_list)
		{
				// print_debug_lexer_list(msh->lexer_list, "main after lexer"); // à supprimer à terme
			//print_debug_lexer_list(msh->lexer_list, "main lexer_list"); // à supprimer à terme
			parser(msh);
				// print_debug_lexer_list(msh->lexer_list, "main after parser"); // à supprimer à terme
		}
		if (!(msh->return_code) && msh->lexer_list)
		{
			expander(msh); // à réviser avec l'env propre à minishell
				// print_debug_lexer_list(msh->lexer_list, "main lexer_list"); // à supprimer à terme
				// print_debug_exp_list(msh->exp_list, "main expander_list"); // à supprimer à terme

			if (expander_list_is_empty(msh->exp_list) == TRUE && (msh->exp_current_type == R_ORIGIN_REDIRECT || msh->exp_current_type == W_DEST_REDIRECT || msh->exp_current_type == WA_DEST_REDIRECT || msh->exp_current_type == LIMITER_HEREDOC))
				exit_no_file_directory("");
			else if (expander_list_is_empty(msh->exp_list) == TRUE )
				exit_command_not_foud("");
		}
		if (!(msh->return_code) && msh->lexer_list)
		{
			build_exec_list(msh);
			execution(msh);
		}
		clean_msh_list(msh);
	}
	clear_history();
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
CONTEXTE DE CETTE REFLEXION :
lexer, parser, expander, executor, conditionné à msh->return_code == 0

au démarrage, avant la boucle
msh->return_code = 0
msh->stored_return_code = 0

boucle :
	msh->stored_return_code = msh->return_code;
	msh->return_code = 0
	prompt saisi :
		si erreur au lexer/parser :
			return_code = 2 (par exemple) => expander et executor ne sont pas atteints
				retour au prompt
		sinon (msh->return_code toujours à 0 donc):
			expander atteint (pas d'erreur possible dans l'expander):
				$? remplacé par msh->stored_return_code
			executor atteint :
				si erreur :
					msh->return_code = 127 (par exemple)
				sinon
					msh->return_code laissé à 0
				retour au prompt

*/
