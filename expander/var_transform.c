/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:18:00 by amennad           #+#    #+#             */
/*   Updated: 2023/11/24 17:27:18 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	what_else_again(t_lexer_list *tmp, char **str, int *not_exist_var)
{
	if (*str != NULL && *not_exist_var == 1 && ft_strlen(tmp->str) == 0
		&& tmp->next == NULL)
	{
		*str = NULL;
		*str = ft_strdup("");
		*not_exist_var = 0;
	}
	else if (*str != NULL && *not_exist_var == 1 && ft_strlen(tmp->str) > 0)
	{
		*str = NULL;
		*str = ft_strdup("");
		all_in_str(str, tmp->str);
		*not_exist_var = 0;
	}
	else if (*str == NULL && *not_exist_var == 1 && ft_strlen(tmp->str) > 0)
	{
		all_in_str(str, tmp->str);
	}
}

void	what_else(t_msh *msh, t_lexer_list *tmp, char **str, int *not_exist_var)
{
	if (msh->exp_current_type == R_ORIGIN_REDIRECT
		|| msh->exp_current_type == W_DEST_REDIRECT
		|| msh->exp_current_type == WA_DEST_REDIRECT)
	{
		what_else_again(tmp, str, not_exist_var);
	}
	else if (ft_strlen(tmp->str) > 0 && !*str && *not_exist_var == 1)
	{
		all_in_str(str, tmp->str);
		*not_exist_var = 0;
	}
	else if (ft_strlen(tmp->str) > 0 && *str && *not_exist_var == 1)
	{
		*str = NULL;
		*str = ft_strdup("");
		all_in_str(str, tmp->str);
		*not_exist_var = 0;
	}
	else if (*not_exist_var == 0)
		all_in_str(str, tmp->str);
}

int	is_big_conditional(t_msh *msh, t_lexer_list *tmp, char **str,
		int *not_exist_var)
{
	if ((tmp->lexer_type > 4 && tmp->lexer_type < 10))
		return (1);
	else if (tmp->lexer_type == RETURN_VALUE)
		is_return_value(tmp, str, not_exist_var);
	else if (tmp->lexer_type == D_QUOTE_VAR)
		db_quote_var_trans(msh, tmp, str, not_exist_var);
	else if (tmp->lexer_type == VARIABLE)
	{
		that_is_variable(msh, tmp, str, not_exist_var);
		if (*not_exist_var == 3)
			return (1);
	}
	else if (tmp && tmp->lexer_type == WORD)
	{
		if (that_is_wold(msh, tmp, str, not_exist_var) == 1)
			return (1);
	}
	else if (msh->exp_current_type == LIMITER_HEREDOC
		&& ft_strlen(tmp->str) > 0)
		all_in_str(str, tmp->str);
	else if (msh->lexer_list->lexer_type == SPECIAL_VAR)
		is_special_var(msh, tmp, str);
	else if (tmp && tmp->lexer_type >= 2 && tmp->lexer_type < 4)
		what_else(msh, tmp, str, not_exist_var);
	return (0);
}

t_lexer_list	*generate_str(t_msh *msh, t_lexer_list *tmp)
{
	char	*str;
	int		not_exist_var;
	int		is_break;

	str = NULL;
	not_exist_var = 1;
	while (tmp)
	{
		is_break = is_big_conditional(msh, tmp, &str, &not_exist_var);
		if (is_break == 1)
			break ;
		else if (tmp->lexer_type == PIPE)
			break ;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
		not_exist_var = 1;
	}
	the_end(msh, tmp, &str, not_exist_var);
	return (tmp);
}
