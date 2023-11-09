/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_other_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:12:31 by amennad           #+#    #+#             */
/*   Updated: 2023/11/09 16:17:30 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_blank(t_msh *msh, char *prompt, int *i)
{
	lexer_push(msh, ft_strdup(" "), BLANK);
	if (prompt[*i + 1] == ' ' || prompt[*i + 1] == '\t')
	{
		while (prompt[*i] == ' ' || prompt[*i] == '\t')
		{
			*i += 1;
		}
		*i -= 1;
	}
	return (0);
}

int	is_pipe(t_msh *msh, char *prompt, int *i)
{
	if (*i == 0 || prompt[*i + 1] == '|'
		|| prompt[ft_strlen(prompt) - 1] == '|')
	{
		exit_synthax_error(msh, "|");
		return (2);
	}
	else
		lexer_push(msh, ft_strdup("|"), PIPE);
	return (0);
}
