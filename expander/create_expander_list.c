/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_expander_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:15:34 by amennad           #+#    #+#             */
/*   Updated: 2023/10/27 17:48:43 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	PIPE,
	WORD,
	S_QUOTE,
	D_QUOTE,
	R_REDIRECT,
	HEREDOC,
	W_REDIRECT,
	W_APPEND_REDIRECT,
	BLANK,
	VARIABLE,
	RETURN_VALUE,
	SPECIAL_VAR,
	D_QUOTE_VAR*/
// 	enum	e_expander_type
// {
// 	WORD_EXPANDED,
// 	R_ORIGIN_REDIRECT,
// 	LIMITER_HEREDOC,
// 	W_DEST_REDIRECT,
// 	WA_DEST_REDIRECT,
// 	PIPE_EXPANDED
// };
// 	if (tmp->lexer_type == R_REDIRECT)
// 		type = R_ORIGIN_REDIRECT;
// 	else if (tmp->lexer_type == HEREDOC)
// 		type = LIMITER_HEREDOC;
// 	else if (tmp->lexer_type == W_REDIRECT)
// 		type = W_DEST_REDIRECT;
// 	else if (tmp->lexer_type == W_APPEND_REDIRECT)
// 		type = WA_DEST_REDIRECT;
// 	else if (tmp->lexer_type == PIPE)
// 		type = PIPE_EXPANDED;
// 	else if (tmp->lexer_type == BLANK)
// 		;
// 	else
// 		type = WORD_EXPANDED;

t_lexer_list	*	generate_str(t_msh *msh, t_lexer_list *tmp2, t_exp_type type_name)
{
	char	*str;
	t_lexer_list *tmp;
	str = NULL;
	tmp = tmp2;
	if (tmp->next->lexer_type == BLANK && (tmp->next->next->lexer_type > 0
			&& tmp->next->next->lexer_type < 5))
		tmp = tmp->next;
	if (tmp->next->lexer_type > 0 && tmp->next->lexer_type < 5)
	{
		while (tmp->lexer_type > 0 && tmp->lexer_type < 5)
		{
			if (!str)
				str = ft_one_word(tmp->str);
			else if (str)
				str = ft_join_word(str, tmp->str);
			if (!tmp->next)
				break ;
			tmp = tmp->next;
		}
		expander_push(msh, tmp->next->str, type_name);
	}
	return (tmp);
}

t_lexer_list	* just_simple_word(t_msh *msh, t_lexer_list *tmp)
{
	char	*str;

	str = NULL;
	while (tmp->lexer_type > 0 && tmp->lexer_type < 5)
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
	return (tmp);
}

//NO TUCH
t_lexer_list	*check_lexer_list(t_msh *msh, t_lexer_list *tmp)
{

	printf("check_lexer_list => %s\n", tmp->str);
	printf("check_lexer_list => %u\n", tmp->lexer_type);
	if (tmp && tmp->lexer_type == PIPE)
	{
		expander_push(msh, "|", PIPE_EXPANDED);
		tmp = generate_str(msh, tmp, WORD_EXPANDED);
	}
	else if (tmp->lexer_type == R_REDIRECT)
		tmp = generate_str(msh, tmp, R_ORIGIN_REDIRECT);
	else if (tmp->lexer_type == HEREDOC)
		tmp = generate_str(msh, tmp, LIMITER_HEREDOC);
	else if (tmp->lexer_type == W_REDIRECT)
		tmp = generate_str(msh, tmp, W_DEST_REDIRECT);
	else if (tmp->lexer_type == W_APPEND_REDIRECT)
		tmp = generate_str(msh, tmp, WA_DEST_REDIRECT);
	// else if (tmp->lexer_type == WORD)
	// 	tmp = just_simple_word(msh, tmp);
	return (tmp);
}

void	create_expander_list(t_msh *msh)
{
	t_lexer_list	*tmp;

	tmp = msh->lexer_list;
	while (tmp->next != NULL)
	{
		tmp = check_lexer_list(msh, tmp);
		// if (!tmp->next)
		// {
		// 	if (tmp->lexer_type > 0 && tmp->lexer_type < 4)
		// 		expander_push(msh, tmp->str, WORD_EXPANDED);
		// 	break ;
		// }
		tmp = tmp->next;
	}
	// printf("create_expander_listend str => %s\n", tmp->str);
	print_debug_exp_list(msh->exp_list, "exp list");
}
