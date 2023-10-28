/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_expander_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:15:34 by amennad           #+#    #+#             */
/*   Updated: 2023/10/28 16:00:25 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int ft_msh_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			return (i);
		}
		i++;
	}
	if (s[i] == (char)c)
	{
		return (i);
	}
	return (-1);
}

void	all_in_str(char **str, char *str_value)
{
	if (!*str)
		*str = ft_one_word(str_value);
	else if (*str)
		*str = ft_join_word(*str, str_value);
}

t_lexer_list	*generate_str(t_msh *msh, t_lexer_list *tmp,
		t_exp_type type_name)
{
	char	*str;

	str = NULL;
	while (tmp)
	{
		if ((tmp->lexer_type > 4 && tmp->lexer_type < 10)
			|| tmp->lexer_type == 0)
			break ;
		else if (tmp->lexer_type == VARIABLE || tmp->lexer_type == RETURN_VALUE)
		{
			if (msh->exp_current_type == LIMITER_HEREDOC)
			{
				all_in_str(&str, tmp->var_name);
			}
			else if (tmp->lexer_type == VARIABLE)
			{
				if (tmp->var_value)
					all_in_str(&str, tmp->var_value);
				else if (msh->exp_current_type == R_ORIGIN_REDIRECT ||
						msh->exp_current_type == W_DEST_REDIRECT ||
						msh->exp_current_type == WA_DEST_REDIRECT)
					all_in_str(&str, tmp->var_name);
			}
			else if (tmp->lexer_type == RETURN_VALUE)
			{
				if (!tmp->var_value)
					all_in_str(&str, "0");
				else
					all_in_str(&str, tmp->var_value);
			}
		}
		else if (tmp->lexer_type == D_QUOTE_VAR)
		{int dollar_pos = ft_msh_strchr(tmp->str, '$');
			int len = ft_strlen(tmp->str);


			char *start_str = ft_substr(tmp->str, 0, dollar_pos);
			char *end_str = ft_substr(tmp->str, dollar_pos + ft_strlen(tmp->var_name) , len);
			printf("start_str: %s\n", start_str);
			printf("end_str: %s\n", end_str);
			if (tmp->var_value)
			{
				str = ft_strjoin(start_str, tmp->var_value );
				str = ft_strjoin(str, end_str);
			}
			else
			{
				str = ft_strjoin(start_str, end_str);
			}
			printf("str: %s\n", str);
		}
		else if (tmp && tmp->lexer_type > 0 && tmp->lexer_type < 5)
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
	return (tmp);
}

void	defined_type(t_msh *msh, t_lexer_list *tmp)
{
	if (tmp && tmp->lexer_type == PIPE)
		msh->exp_current_type = WORD_EXPANDED;
	else if (tmp->lexer_type == R_REDIRECT)
		msh->exp_current_type = R_ORIGIN_REDIRECT;
	else if (tmp->lexer_type == HEREDOC)
		msh->exp_current_type = LIMITER_HEREDOC;
	else if (tmp->lexer_type == W_REDIRECT)
		msh->exp_current_type = W_DEST_REDIRECT;
	else if (tmp->lexer_type == W_APPEND_REDIRECT)
		msh->exp_current_type = WA_DEST_REDIRECT;
}

//NO TUCH
t_lexer_list	*check_lexer_list(t_msh *msh, t_lexer_list *tmp)
{
	defined_type(msh, tmp);
	if (tmp && tmp->lexer_type == PIPE)
	{
		expander_push(msh, "|", PIPE_EXPANDED);
		tmp = generate_str(msh, tmp, WORD_EXPANDED);
	}
	else if (msh->exp_current_type == R_ORIGIN_REDIRECT)
		tmp = generate_str(msh, tmp, R_ORIGIN_REDIRECT);
	else if (msh->exp_current_type == LIMITER_HEREDOC)
		tmp = generate_str(msh, tmp, LIMITER_HEREDOC);
	else if (msh->exp_current_type == W_DEST_REDIRECT)
		tmp = generate_str(msh, tmp, W_DEST_REDIRECT);
	else if (msh->exp_current_type == WA_DEST_REDIRECT)
		tmp = generate_str(msh, tmp, WA_DEST_REDIRECT);
	else if (msh->exp_current_type == WORD_EXPANDED)
		tmp = generate_str(msh, tmp, WORD_EXPANDED);
	return (tmp);
}

void	create_expander_list(t_msh *msh)
{
	t_lexer_list	*tmp;

	tmp = msh->lexer_list;
	while (tmp)
	{
		tmp = check_lexer_list(msh, tmp);
		tmp = tmp->next;
	}
	print_debug_exp_list(msh->exp_list, "exp list");
}
