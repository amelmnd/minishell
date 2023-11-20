/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:18:00 by amennad           #+#    #+#             */
/*   Updated: 2023/11/20 20:10:38 by amennad          ###   ########.fr       */
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

void is_return_value(t_lexer_list *tmp, char **str, t_bool *not_exist_var)
{
	*not_exist_var = FALSE;
	if (!tmp->var_value)
	{
		char *tmp_str = ft_strdup("0");
		all_in_str(str, tmp_str);
		free_chars(&tmp_str);
	}
	else
		all_in_str(str, tmp->var_value);
}

void	db_quote_var_trans(t_lexer_list *tmp, char **str, t_bool *not_exist_var)
{
	int		dollar_pos;
	int		len;
	char	*start_str;
	char	*end_str;

	*not_exist_var = FALSE;
	dollar_pos = ft_msh_strchr(tmp->str, '$');
	len = ft_strlen(tmp->str);
	start_str = ft_substr(tmp->str, 0, dollar_pos);
	end_str = ft_substr(tmp->str, dollar_pos + ft_strlen(tmp->var_name), len);
	if (*not_exist_var == TRUE)
			*str = ft_strdup(NULL);
	if (tmp->var_value)
	{
		*str = ft_strjoin(start_str, tmp->var_value);
		*str = ft_strjoin(*str, end_str);
	}
	else
		*str = ft_strjoin(start_str, end_str);
}

void is_special_var(t_lexer_list *tmp, char **str, t_bool *not_exist_var)
{
	if ((*not_exist_var == TRUE && tmp->next->lexer_type > 4 && tmp->next->lexer_type <= 9) || !*str)
		all_in_str(str, tmp->str);
	else
	{
		char *tmp_str = ft_strdup("");
		all_in_str(str, tmp_str);
		free_chars(&tmp_str);
	}
}

void is_variable(t_lexer_list *tmp, char **str, t_bool *not_exist_var, t_exp_type type_name)
{
	if (tmp->var_value && type_name != LIMITER_HEREDOC)
	{
		if (*not_exist_var == TRUE)
		{
			*str = ft_strdup(NULL);
			all_in_str(str, tmp->var_value);

		}
		else if (*not_exist_var == FALSE)
			all_in_str(str, tmp->var_value);
		*not_exist_var = FALSE;
	}
	else if (*not_exist_var == TRUE && (!tmp->var_value || !tmp->str) && (type_name != R_ORIGIN_REDIRECT ||
	type_name != W_DEST_REDIRECT || type_name != WA_DEST_REDIRECT ))
		all_in_str(str, tmp->var_name);
	else if (*not_exist_var == FALSE && !tmp->var_value)
	{
		char *tmp_str = ft_strdup("");
		all_in_str(str, tmp_str);
		free_chars(&tmp_str);
	}
}

t_lexer_list	*generate_str(t_msh *msh, t_lexer_list *tmp,
		t_exp_type type_name)
{
	char	*str;
	t_bool	not_exist_var;

	str = NULL;
	not_exist_var = TRUE;
	while (tmp)
	{
		if (tmp->lexer_type == R_REDIRECT || tmp->lexer_type == HEREDOC || tmp->lexer_type == W_REDIRECT || tmp->lexer_type == W_APPEND_REDIRECT || tmp->lexer_type == PIPE || tmp->lexer_type == BLANK)
			break ;
		else if (tmp->lexer_type == RETURN_VALUE) //✅
			is_return_value(tmp, &str, &not_exist_var);
		else if (tmp->lexer_type == D_QUOTE_VAR)//✅
			db_quote_var_trans(tmp, &str, &not_exist_var);
		else if (tmp->lexer_type == SPECIAL_VAR)
			is_special_var(tmp, &str, &not_exist_var);
		else if (tmp->lexer_type == VARIABLE)
			is_variable(tmp, &str, &not_exist_var, type_name);
		else if (tmp && tmp->lexer_type > 0 && tmp->lexer_type < 4)
		{
			if (not_exist_var == TRUE)
				str = ft_strdup(NULL);
			all_in_str(&str, tmp->str);
			not_exist_var = FALSE;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (str)
	{
		if (not_exist_var == TRUE && (type_name == R_ORIGIN_REDIRECT || type_name == W_DEST_REDIRECT || type_name == WA_DEST_REDIRECT))
			expander_push(msh, str, AMBIGUOUS_REDIRECT);
		else
			expander_push(msh, str, type_name);
		msh->exp_current_type = WORD_EXPANDED;
	}
	else
	{
		expander_push(msh, str, type_name);}
	//free_chars(&str);
	return (tmp);
}
