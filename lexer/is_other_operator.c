/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_other_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:12:31 by amennad           #+#    #+#             */
/*   Updated: 2023/11/17 17:30:55 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_blank(t_msh *msh, char *prompt, int *i)
{
	char *str;

	str = ft_strdup(" ");
	lexer_push(msh, str, BLANK);
	if (prompt[*i + 1] == ' ' || prompt[*i + 1] == '\t')
	{
		while (prompt[*i] == ' ' || prompt[*i] == '\t')
		{
			*i += 1;
		}
		*i -= 1;
	}
	free_chars(&str);
	return (0);
}

int	is_pipe(t_msh *msh, char *prompt, int *i)
{
	char *str;


	if (*i == 0 || prompt[*i + 1] == '|'
		|| prompt[ft_strlen(prompt) - 1] == '|')
	{
		exit_synthax_error(msh, "|");
		return (2);
	}
	else
	{
		str = ft_strdup("|");
		lexer_push(msh, str, PIPE);
		free_chars(&str);
	}
	return (0);
}
