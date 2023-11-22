/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_fn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:52:28 by amennad           #+#    #+#             */
/*   Updated: 2023/11/22 21:35:04 by amennad          ###   ########.fr       */
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

void	db_quote_var_trans(t_msh *msh, t_lexer_list *tmp, char **str, int *not_exist_var)
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