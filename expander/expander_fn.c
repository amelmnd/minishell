/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_fn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:52:28 by amennad           #+#    #+#             */
/*   Updated: 2023/11/25 05:03:38 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	all_in_str(t_msh *msh, char *str_value)
{
	if (!(msh->transexp))
	{
		free_chars(&(msh->transexp));
		msh->transexp = ft_one_word(str_value);
	}
	else
	{
		free_chars(&(msh->temp));
		msh->temp = ft_strdup(msh->transexp);
		free_chars(&(msh->transexp));
		msh->transexp = ft_join_word(msh->temp, str_value);
		free_chars(&(msh->temp));
	}
}

void	db_quote_var_trans(t_msh *msh, t_lexer_list *tmp, int *not_exist_var)
{
	int		dollar_pos;
	int		len;
	char	*start_str;
	char	*end_str;

	if (msh->exp_current_type == LIMITER_HEREDOC)
	{
		free_chars(&(msh->transexp));
		msh->transexp = ft_strdup(tmp->str);
		return ;
	}
	dollar_pos = ft_msh_strchr(tmp->str, '$');
	len = ft_strlen(tmp->str);
	start_str = ft_substr(tmp->str, 0, dollar_pos);
	end_str = ft_substr(tmp->str, dollar_pos + ft_strlen(tmp->var_name), len);
	if (tmp->var_value)
		musical_chairs(msh, start_str, tmp, end_str);
	else
	{
		free_chars(&(msh->transexp));
		msh->transexp = ft_strjoin(start_str, end_str);
	}
	*not_exist_var = 0;
	free_chars(&start_str);
	free_chars(&end_str);
}

void	is_return_value(t_msh *msh, t_lexer_list *tmp, int *not_exist_var)
{
	if (!tmp->var_value)
		all_in_str(msh, "0");
	else
		all_in_str(msh, tmp->var_value);
	*not_exist_var = 0;
}

int	check_word(t_msh *msh, t_lexer_list *tmp)
{
	if ((ft_strlen(tmp->str) == 1 && ft_strcmp(tmp->str, "$") == 1)
		&& msh->exp_current_type != LIMITER_HEREDOC)
	{
		if ((tmp->previous == NULL || (ft_strlen(msh->transexp) == 0
					&& tmp->previous->previous == NULL )) && tmp->next
			&& (tmp->next->lexer_type == D_QUOTE
				|| tmp->next->lexer_type == S_QUOTE)
			&& ft_strlen(tmp->next->str) == 0)
		{
			free_chars(&(msh->transexp));
			msh->transexp = ft_strdup("\'\'");
			return (1);
		}
		else if (tmp->next && (tmp->next->lexer_type == D_QUOTE
				|| tmp->next->lexer_type == S_QUOTE)
			&& ft_strlen(tmp->next->str) == 0)
		{
			free_chars(&(msh->transexp));
			msh->transexp = ft_strdup("");
			return (1);
		}
	}
	return (0);
}

void	the_end(t_msh *msh, t_lexer_list *tmp, int not_exist_var)
{
	if (tmp->lexer_type == PIPE)
	{
		if (msh->transexp && ft_strlen(msh->transexp) > 0)
			expander_push(msh, msh->transexp, msh->exp_current_type);
		expander_push(msh, "|", PIPE_EXPANDED);
	}
	else if (msh->transexp && (not_exist_var == 2 || not_exist_var == 3))
	{
		expander_push(msh, msh->transexp, AMBIGOUS_REDIRECT_EXP);
		msh->exp_current_type = WORD_EXPANDED;
	}
	else if (ft_strcmp(msh->transexp, "\'\'") == 1)
	{
		expander_push(msh, msh->transexp, msh->exp_current_type);
		msh->exp_current_type = WORD_EXPANDED;
	}
	else if (ft_strlen(msh->transexp) > 0)
	{
		expander_push(msh, msh->transexp, msh->exp_current_type);
		msh->exp_current_type = WORD_EXPANDED;
	}
}
