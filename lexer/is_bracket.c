/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bracket.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:14:34 by amennad           #+#    #+#             */
/*   Updated: 2023/10/26 09:36:17 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_right_bracket(t_msh *msh, char *prompt, int *i)
{
	if (prompt[*i + 1] != '>' && prompt[*i + 1] != '|')
		lexer_push(msh, ">", W_REDIRECT);
	if (prompt[*i + 1] == '|')
	{
		exit_synthax_error("newline");
		return (258);
	}
	if (prompt[*i + 1] == '>')
	{
		if (prompt[*i + 2] == '>' || prompt[*i + 2] == '|')
		{
			if (prompt[*i + 2] == '>')
				exit_synthax_error(">");
			else if (prompt[*i + 2] == '|')
				exit_synthax_error("|");
			return (258);
		}
		else
			lexer_push(msh, ">>", W_APPEND_REDIRECT);
		*i += 1;
	}
	return (0);
}

int	is_left_bracket(t_msh *msh, char *prompt, int *i)
{
	if (prompt[*i + 1] != '<' && prompt[*i + 1] != '|')
		lexer_push(msh, "<", R_REDIRECT);
	if (prompt[*i + 1] == '|')
	{
		exit_synthax_error("|");
		return (258);
	}
	if (prompt[*i + 1] == '<')
	{
		if (prompt[*i + 2] == '<' || prompt[*i + 2] == '|')
		{
			if (prompt[*i + 2] == '<')
				exit_synthax_error("<");
			else if (prompt[*i + 2] == '|')
				exit_synthax_error("|");
			return (258);
		}
		else
			lexer_push(msh, "<<", HEREDOC);
		*i += 1;
	}
	return (0);
}
