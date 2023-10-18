/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexer_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:07:48 by amennad           #+#    #+#             */
/*   Updated: 2023/10/18 14:59:12 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_create_list(t_msh *msh, char *prompt)
{
	int	i;
	int	return_code;

	i = 0;
	return_code = 0;
	while (i < ft_strlen(prompt))
	{
		// printf("prompt[%d] = %c\n", i, prompt[i]);
		if (prompt[i] == '|')
			return_code = is_pipe(msh, prompt, &i);
		else if (prompt[i] == ' ' || prompt[i] == '\t')
			return_code = is_blank(msh, prompt, &i);
		else if (prompt[i] == '>')
			return_code = is_right_bracket(msh, prompt, &i);
		else if (prompt[i] == '<')
			return_code = is_left_bracket(msh, prompt, &i);
		else if (prompt[i] == 39)
			return_code = is_simple_quote(msh, prompt, &i);
		if (return_code != 0)
		{
			msh->return_code = return_code;
			break ;
		}
		i++;
	}
	return (return_code);
}
