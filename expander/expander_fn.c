/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_fn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:52:28 by amennad           #+#    #+#             */
/*   Updated: 2023/11/24 17:24:29 by amennad          ###   ########.fr       */
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

void	db_quote_var_trans(t_msh *msh, t_lexer_list *tmp, char **str,
int *not_exist_var)
{
	int		dollar_pos;
	int		len;
	char	*start_str;
	char	*end_str;

	if (msh->exp_current_type == LIMITER_HEREDOC)
	{
		*str = ft_strdup(tmp->str);
		return ;
	}
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
	*not_exist_var = 0;
	free_chars(&start_str);
	free_chars(&end_str);
}

void	is_return_value(t_lexer_list *tmp, char **str, int *not_exist_var)
{
	char	*tmp_str;

	if (!tmp->var_value)
	{
		tmp_str = ft_strdup("0");
		all_in_str(str, tmp_str);
		free_chars(&tmp_str);
	}
	else
		all_in_str(str, tmp->var_value);
	*not_exist_var = 0;
}

int	check_word(t_msh *msh, t_lexer_list *tmp, char **str)
{
	if ((ft_strlen(tmp->str) == 1 && ft_strcmp(tmp->str, "$") == 1)
		&& msh->exp_current_type != LIMITER_HEREDOC)
	{
		if ((tmp->previous == NULL || (ft_strlen(*str) == 0
					&& tmp->previous->previous == NULL )) && tmp->next
			&& (tmp->next->lexer_type == D_QUOTE
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

void	the_end(t_msh *msh, t_lexer_list *tmp, char **str, int not_exist_var)
{
	if (tmp->lexer_type == PIPE)
	{
		if (*str && ft_strlen(*str) > 0)
			expander_push(msh, *str, msh->exp_current_type);
		expander_push(msh, ft_strdup("|"), PIPE_EXPANDED);
	}
	else if (*str && (not_exist_var == 2 || not_exist_var == 3))
	{
		expander_push(msh, *str, AMBIGOUS_REDIRECT_EXP);
		msh->exp_current_type = WORD_EXPANDED;
	}
	else if (ft_strcmp(*str, "\'\'") == 1)
	{
		expander_push(msh, *str, msh->exp_current_type);
		msh->exp_current_type = WORD_EXPANDED;
	}
	else if (ft_strlen(*str) > 0)
	{
		expander_push(msh, *str, msh->exp_current_type);
		msh->exp_current_type = WORD_EXPANDED;
	}
}
