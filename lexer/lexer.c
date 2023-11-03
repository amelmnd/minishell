/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:48:20 by amennad           #+#    #+#             */
/*   Updated: 2023/11/02 18:46:57 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	prompt_isempty(char **prompt)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(*prompt);
	while (i < len)
	{
		if ((*prompt)[i] != ' ' && (*prompt)[i] != '\t')
		{
			*prompt = ft_substr(*prompt, i, (len - i));
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	lexer_check(t_msh *msh, char *prompt)
{
	if (prompt_isempty(&prompt) == TRUE)
	{
		msh->return_code = 0;
		exit_new_line();
	}
	else
		lexer_create_list(msh, prompt);
}
