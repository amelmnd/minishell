/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bracket.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:14:34 by amennad           #+#    #+#             */
/*   Updated: 2023/11/21 19:03:47 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	generate_lexer_list(t_msh *msh, char *str, t_lexer_type type)
{
	char	*tmp_str;

	tmp_str = ft_strdup(str);
	lexer_push(msh, tmp_str, type);
	free_chars(&tmp_str);
}

int	is_right_bracket(t_msh *msh, char *prompt, int *i)
{
	if (prompt[*i + 1] != '>' && prompt[*i + 1] != '|')
		generate_lexer_list(msh, ">", W_REDIRECT);
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
			generate_lexer_list(msh, ">>", W_APPEND_REDIRECT);
		*i += 1;
	}
	return (0);
}

int	is_left_bracket(t_msh *msh, char *prompt, int *i)
{
	if (prompt[*i + 1] != '<' && prompt[*i + 1] != '|')
		generate_lexer_list(msh, "<", R_REDIRECT);
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
			generate_lexer_list(msh, "<<", HEREDOC);
		*i += 1;
	}
	return (0);
}
