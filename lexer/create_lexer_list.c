/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lexer_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:07:48 by amennad           #+#    #+#             */
/*   Updated: 2023/10/18 10:18:54 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_pipe(t_msh *msh, char *prompt, int *i)
{
	if (*i == 0 || prompt[*i + 1] == '|' || prompt[ft_strlen(prompt) - 1] == '|')
	{
		exit_synthax_error(msh, '|');
		return (258);
	}
	else
		lexer_push(msh, "|", PIPE);
	return (0);
}

int is_blank(t_msh *msh, char *prompt, int *i)
{
	lexer_push(msh, " ", BLANK);
	if (prompt[*i + 1] == ' ' || prompt[*i + 1] == '\t')
	{
		while (prompt[*i] == ' ' || prompt[*i] == '\t')
		{
			*i += 1;
		}
		*i -= 1;
	}
	printf("i = %d\n", *i);
	return (0);
}

int lexer_create_list(t_msh *msh, char *prompt)
{
	int i;
	int return_code;

	i = 0;
	return_code = 0;
	while (i < ft_strlen(prompt))
	{
		printf("prompt[%d] = %c\n", i, prompt[i]);
		if (prompt[i] == '|')
			return_code = is_pipe(msh, prompt, &i);
		else if (prompt[i] == ' ' || prompt[i] == '\t')
			return_code = is_blank(msh, prompt, &i);
		if (return_code != 0)
		{
			msh->return_code = return_code;
			break;
		}
		i++;
	}
	return (return_code);
}
