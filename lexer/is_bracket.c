/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bracket.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:14:34 by amennad           #+#    #+#             */
/*   Updated: 2023/11/17 15:07:38 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_right_bracket(t_msh *msh, char *prompt, int *i)
{
		char *str;

	if (prompt[*i + 1] != '>' && prompt[*i + 1] != '|')
	{
		str = ft_strdup(">");
		lexer_push(msh, str, W_REDIRECT);
		free_chars(&str);
	}
	if (prompt[*i + 1] == '|')
	{
		exit_synthax_error(msh, "newline");
		return (2);
	}
	if (prompt[*i + 1] == '>')
	{
		if (prompt[*i + 2] == '>' || prompt[*i + 2] == '|')
		{
			if (prompt[*i + 2] == '>')
				exit_synthax_error(msh, ">");
			else if (prompt[*i + 2] == '|')
				exit_synthax_error(msh, "|");
			return (2);
		}
		else
		{
			str = ft_strdup(">>");
			lexer_push(msh, str, W_APPEND_REDIRECT);
			free_chars(&str);
		}
		*i += 1;
	}
	return (0);
}

int	is_left_bracket(t_msh *msh, char *prompt, int *i)
{
	char *str;

	if (prompt[*i + 1] != '<' && prompt[*i + 1] != '|')
	{
		str = ft_strdup("<");
		lexer_push(msh, str, R_REDIRECT);
		free_chars(&str);
	}
	if (prompt[*i + 1] == '|')
	{
		exit_synthax_error(msh, "|");
		return (2);
	}
	if (prompt[*i + 1] == '<')
	{
		if (prompt[*i + 2] == '<' || prompt[*i + 2] == '|')
		{
			if (prompt[*i + 2] == '<')
				exit_synthax_error(msh, "<");
			else if (prompt[*i + 2] == '|')
				exit_synthax_error(msh, "|");
			return (2);
		}
		else
		{
			str = ft_strdup("<<");
			lexer_push(msh, str, HEREDOC);
			free_chars(&str);
		}
		*i += 1;
	}
	return (0);
}
