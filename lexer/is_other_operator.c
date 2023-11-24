/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_other_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:12:31 by amennad           #+#    #+#             */
/*   Updated: 2023/11/24 18:11:20 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_blank(t_msh *msh, char *prompt, int *i)
{
	char	*tmp_str;

	tmp_str = ft_strdup(" ");
	lexer_push(msh, tmp_str, BLANK);
	free_chars(&tmp_str);
	if (prompt[*i + 1] == ' ' || prompt[*i + 1] == '\t')
	{
		while (prompt[*i] == ' ' || prompt[*i] == '\t')
		{
			*i += 1;
		}
		*i -= 1;
	}
	return (msh->return_code);
}

int	is_pipe(t_msh *msh, char *prompt, int *i)
{
	char	*tmp_str;

	if (*i == 0 || prompt[*i + 1] == '|'
		|| prompt[ft_strlen(prompt) - 1] == '|')
	{
		exit_synthax_error(msh, "|");
		return (2);
	}
	else
	{
		tmp_str = ft_strdup("|");
		lexer_push(msh, tmp_str, PIPE);
		free_chars(&tmp_str);
	}
	return (msh->return_code);
}
