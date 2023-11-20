/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:48:20 by amennad           #+#    #+#             */
/*   Updated: 2023/11/20 17:43:44 by amennad          ###   ########.fr       */
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
			// free_chars(prompt);
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
		// free_chars(&prompt);
		exit_new_line(msh);
		return ;
	}
	else
	{
		add_history(msh->prompt); // TODO verifier le fonctionnement avec les signaux et le heredoc fini

		lexer_create_list(msh, prompt);
		free_chars(&prompt);
	}
	//free_chars(&prompt);
}
