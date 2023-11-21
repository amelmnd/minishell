/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:18:00 by amennad           #+#    #+#             */
/*   Updated: 2023/11/21 11:27:10 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	all_in_str(char **str, char *str_value)
{
	if (!*str)
		*str = ft_one_word(str_value);
	else if (*str)
		*str = ft_join_word(*str, str_value);
}

void	that_is_variable(t_msh *msh, t_lexer_list *tmp, char **str)
{
	if (msh->exp_current_type == LIMITER_HEREDOC)
		all_in_str(str, tmp->var_name);
	else if (tmp->lexer_type == VARIABLE)
	{
		if (tmp->var_value)
			all_in_str(str, tmp->var_value);
		else if (msh->exp_current_type == R_ORIGIN_REDIRECT
				|| msh->exp_current_type == W_DEST_REDIRECT
				|| msh->exp_current_type == WA_DEST_REDIRECT)
			all_in_str(str, tmp->var_name);
	}
	else if (tmp->lexer_type == RETURN_VALUE)
	{
		if (!tmp->var_value)
			all_in_str(str, "0");
		else
			all_in_str(str, tmp->var_value);
	}
}

// NOTE : this is the old function
// void	that_is_variable(t_msh *msh, t_lexer_list *tmp, char **str)
// {
// 	if (msh->exp_current_type == LIMITER_HEREDOC)
// 		all_in_str(str, tmp->var_name);
// 	else if (tmp->lexer_type == VARIABLE)
// 	{
// 		if (tmp->var_value)
// 			all_in_str(str, tmp->var_value);
// 		else if (msh->exp_current_type == R_ORIGIN_REDIRECT
// 				|| msh->exp_current_type == W_DEST_REDIRECT
// 				|| msh->exp_current_type == WA_DEST_REDIRECT)
// 			all_in_str(str, tmp->var_name);
// 	}
// 	else if (tmp->lexer_type == RETURN_VALUE)
// 	{
// 		if (!tmp->var_value)
// 			all_in_str(str, "0");
// 		else
// 			all_in_str(str, tmp->var_value);
// 	}
// }

void	db_quote_var_trans(t_lexer_list *tmp, char **str, t_bool *not_exist_var)
{
	int		dollar_pos;
	int		len;
	char	*start_str;
	char	*end_str;

	dollar_pos = ft_msh_strchr(tmp->str, '$');
	len = ft_strlen(tmp->str);
	start_str = ft_substr(tmp->str, 0, dollar_pos);
	end_str = ft_substr(tmp->str, dollar_pos + ft_strlen(tmp->var_name), len);
	if (tmp->var_value)
	{
		*str = ft_strjoin(start_str, tmp->var_value);
		*str = ft_strjoin(*str, end_str);
	}
	else
		*str = ft_strjoin(start_str, end_str);
	*not_exist_var = FALSE;
}

void	is_return_value(t_lexer_list *tmp, char **str, t_bool *not_exist_var)
{
	char	*tmp_str;

	*not_exist_var = FALSE;
	if (!tmp->var_value)
	{
		tmp_str = ft_strdup("0");
		all_in_str(str, tmp_str);
		free_chars(&tmp_str);
	}
	else
		all_in_str(str, tmp->var_value);
}

int	check_word(t_lexer_list *tmp, char **str)
{
	if (ft_strlen(tmp->str) > 1)
		return (0);
	if (ft_strlen(tmp->str) == 1 && ft_strcmp(tmp->str, "$") == 1)
	{
		if (tmp->previous == NULL && tmp->next && (tmp->next->lexer_type == D_QUOTE
					|| tmp->next->lexer_type == S_QUOTE)
				&& ft_strlen(tmp->next->str) == 0)
			{
				*str = NULL;
				*str = ft_strdup("\'\'");
				return (1);
			}
		else if (tmp->next && (tmp->next->lexer_type == D_QUOTE
					|| tmp->next->lexer_type == S_QUOTE)
				&& ft_strlen(tmp->next->str) == 0)
			{
				*str = NULL;
				*str = ft_strdup("");
				return (1);
			}
	}
	return (0);
}

t_lexer_list	*generate_str(t_msh *msh, t_lexer_list *tmp,
		t_exp_type type_name)
{
	char	*str;
	t_bool	not_exist_var;
	int		str_check;

	str = NULL;
	not_exist_var = TRUE;
	while (tmp)
	{
		if ((tmp->lexer_type > 4 && tmp->lexer_type < 10)
			|| tmp->lexer_type == 0)
			break ;
		else if (tmp->lexer_type == VARIABLE)
			that_is_variable(msh, tmp, &str);
		else if (tmp->lexer_type == RETURN_VALUE)
			is_return_value(tmp, &str, &not_exist_var);
		else if (tmp->lexer_type == D_QUOTE_VAR)
			db_quote_var_trans(tmp, &str, &not_exist_var);
		else if (tmp && tmp->lexer_type == WORD)
		{
			str_check = check_word(tmp, &str);
			if (str_check == 0)
				all_in_str(&str, tmp->str);
			else if (str_check == 1)

				break ;
		}
		else if (tmp && tmp->lexer_type >= 2 && tmp->lexer_type < 5)
			all_in_str(&str, tmp->str);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (str)
	{
		expander_push(msh, str, type_name);
		msh->exp_current_type = WORD_EXPANDED;
	}
	else if (!str && type_name != R_ORIGIN_REDIRECT &&
				type_name != W_DEST_REDIRECT && type_name != WA_DEST_REDIRECT)
		expander_push(msh, "", WORD_EXPANDED);
	//free_chars(&str);
	return (tmp);
}
