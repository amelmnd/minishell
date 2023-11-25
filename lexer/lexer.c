/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:48:20 by amennad           #+#    #+#             */
/*   Updated: 2023/11/25 05:09:53 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	prompt_isempty(t_msh *msh)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	len = ft_strlen(msh->prompt);
	while (i < len)
	{
		if (msh->prompt[i] != ' ' && msh->prompt[i] != '\t')
		{
			temp = ft_strdup(msh->prompt);
			free_chars(&(msh->prompt));
			msh->prompt = ft_substr(temp, i, (len - i));
			free_chars(&(temp));
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	lexer_check(t_msh *msh)
{
	if (prompt_isempty(msh) == TRUE)
		exit_new_line(msh);
	else
	{
		add_history(msh->prompt);
		lexer_create_list(msh);
	}
}
