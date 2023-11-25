/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:11:01 by amennad           #+#    #+#             */
/*   Updated: 2023/11/25 05:38:13 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	var_exist(t_msh *msh, char *var_name)
{
	t_env_list	*tmp;

	// on peut déplacer cette fonction ailleurs ?
	tmp = msh->env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var_name) == 0)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

void	around_the_readline(t_msh *msh)
{
	if (msh)
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
	}
}

void	expander_exceptions(t_msh *msh)
{
	if (msh)
	{
		if (expander_list_is_empty(msh->exp_list) == TRUE
			&& (msh->exp_current_type == R_ORIGIN_REDIRECT
				|| msh->exp_current_type == W_DEST_REDIRECT
				|| msh->exp_current_type == WA_DEST_REDIRECT
				|| msh->exp_current_type == LIMITER_HEREDOC))
			exit_no_file_directory("");
		else if (expander_list_is_empty(msh->exp_list) == TRUE)
			exit_command_not_foud("");
	}
}

void	generate_prompt(char *envp[])
{
	t_msh	*msh;

	msh = new_msh();
	env_list_generate(msh, envp);
	build_user_for_prompt(msh);
	while (msh)
	{
		around_the_readline(msh);
		lexer_check(msh);
		if (!(msh->return_code) && msh->lexer_list)
			parser(msh);
		if (!(msh->return_code) && msh->lexer_list)
		{
			expander(msh);
			expander_exceptions(msh);
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
