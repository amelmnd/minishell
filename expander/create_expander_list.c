/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_expander_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:15:34 by amennad           #+#    #+#             */
/*   Updated: 2023/10/27 15:17:44 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



//NO TUCH
t_lexer_list *	check_lexer_list(t_msh *msh, t_lexer_list *tmp)
{
	char	*str;

	str = NULL;
	if (tmp && tmp->lexer_type == BLANK)
	{
		tmp = tmp->next;
		return (tmp);
	}
	if (tmp && tmp->lexer_type == PIPE)
	{
		expander_push(msh, "|", PIPE_EXPANDED);
	}
	if (tmp && tmp->lexer_type > 0 && tmp->lexer_type < 4)
	{
		while (tmp->lexer_type > 0 && tmp->lexer_type < 4 )
		{
			if (!str)
				str = ft_one_word(tmp->str);
			else if (str)
				str = ft_join_word(str, tmp->str);
			if (!tmp->next)
				break ;
			tmp = tmp->next;
		}
		expander_push(msh, str, WORD_EXPANDED);
		if (!tmp)
			printf("tmp is null\n");
	}
	return (tmp);
}

void	create_expander_list(t_msh *msh)
{
	t_lexer_list	*tmp;

	tmp = msh->lexer_list;
	while (tmp->next)
	{
		tmp = check_lexer_list(msh, tmp);
		if (!tmp->next)
		{
			if (tmp->lexer_type > 0 && tmp->lexer_type < 4)
				expander_push(msh, tmp->str, WORD_EXPANDED);
			break ;
		}
		tmp = tmp->next;
	}
	print_debug_exp_list(msh->exp_list, "exp list");
}
