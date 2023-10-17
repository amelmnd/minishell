/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexer_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:07:48 by amennad           #+#    #+#             */
/*   Updated: 2023/10/17 17:41:05 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(t_msh *msh, char *prompt, int *i)
{
	if (*i == 0 || prompt[*i + 1] == '|')
	{
		exit_synthax_error(msh, '|');
		return (258);
	}
	else
		lexer_push(msh, "|", PIPE);
	return (0);
}

int	lexer_create_list(t_msh *msh, char *prompt)
{
	int	i;
	int	return_code;

	i = 0;
	return_code = 0;
	while (i < ft_strlen(prompt))
	{
		if (prompt[i] == '|')
			return_code = is_pipe(msh, prompt, &i);
		if (return_code != 0)
		{
			msh->return_code = return_code;
			break ;
		}
		i++;
	}
	return (return_code);
}
