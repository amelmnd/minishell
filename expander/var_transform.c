/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:18:00 by amennad           #+#    #+#             */
/*   Updated: 2023/11/24 12:47:41 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




void	that_is_variable(t_msh *msh, t_lexer_list *tmp, char **str,
		int *not_exist_var)
{
	if (msh->exp_current_type == LIMITER_HEREDOC)
		all_in_str(str, tmp->var_name);
	else if (msh->exp_current_type == R_ORIGIN_REDIRECT
			|| msh->exp_current_type == W_DEST_REDIRECT
			|| msh->exp_current_type == WA_DEST_REDIRECT)
	{
		if (tmp->var_value == NULL && *not_exist_var == 1
			&& ft_strlen(*str) == 0 && *str != NULL)
		{
				all_in_str(str, "");
		}
		else  if (tmp->var_value == NULL && *not_exist_var == 1  &&
        ((tmp->next && (tmp->next->lexer_type == D_QUOTE || tmp->next->lexer_type == S_QUOTE) && ft_strlen(tmp->next->str) == 0) || (tmp->previous && (tmp->previous->lexer_type == D_QUOTE || tmp->previous->lexer_type == S_QUOTE) && ft_strlen(tmp->previous->str) == 0)))
		{
			all_in_str(str, "");
			// *not_exist_var = 0;
		}
		else if (tmp->var_value == NULL && *not_exist_var == 1  && (ft_strlen(*str) == 0 || *str == NULL))
		{
			while (tmp && (tmp->lexer_type == VARIABLE ))
			{
				all_in_str(str, tmp->var_name);
				if (tmp->next == NULL)
					break ;
				tmp = tmp->next;
			}
			if (tmp->next == NULL)
				*not_exist_var = 3;
			else
				*not_exist_var = 2;
		}
		else if (tmp->var_value == NULL && str && *not_exist_var == 0)
		{
				all_in_str(str, "");
		}
		else if (tmp->var_value && !str)
		{
			all_in_str(str, tmp->var_value);
			*not_exist_var = 0;
		}
		else if (tmp->var_value && str && *not_exist_var == 1)
		{
			if (ft_strlen(*str) == 0)
			{
				all_in_str(str, tmp->var_value);
				*not_exist_var = 0;
			}
			else
			{
				char *tmp_str = ft_strdup("");
				all_in_str(str, tmp_str);
				*not_exist_var = 0;
			}
			// all_in_str(str, *str);
			// *not_exist_var = 0;
		}
		else if (tmp->var_value)
		{	all_in_str(str, tmp->var_value);
			*not_exist_var = 0;
		}
	}
	else if (tmp->var_value)
		all_in_str(str, tmp->var_value);
	else if (!tmp->var_value)
	{
		all_in_str(str, "");
	}
}



int	check_word(t_msh *msh, t_lexer_list *tmp, char **str)
{

	if ((ft_strlen(tmp->str) == 1 && ft_strcmp(tmp->str, "$") == 1) && msh->exp_current_type != LIMITER_HEREDOC)
	{
		if ((tmp->previous == NULL || (ft_strlen(*str) == 0 && tmp->previous->previous == NULL )) && tmp->next
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
	//print return de cette fonction et valeur de str
	return (0);
}

t_lexer_list	*generate_str(t_msh *msh, t_lexer_list *tmp)
{
	char	*str;
	int	not_exist_var;
	int		str_check;

	str = NULL;
	not_exist_var = 1;
	// msh->exp_current_type = msh->exp_current_type;
	while (tmp)
	{

	// print_exp_list(msh->exp_list);
		if ((tmp->lexer_type > 4 && tmp->lexer_type < 10))
			break ;
		else if (tmp->lexer_type == RETURN_VALUE) // OK
			is_return_value(tmp, &str, &not_exist_var);
		else if (tmp->lexer_type == D_QUOTE_VAR)
			db_quote_var_trans(msh, tmp, &str, &not_exist_var);
		else if (tmp->lexer_type == VARIABLE)
		{
			that_is_variable(msh, tmp, &str, &not_exist_var);
			if (not_exist_var == 3)
				break ;
		}
		else if (tmp && tmp->lexer_type == WORD)
		{
			str_check = check_word(msh, tmp, &str);
			if (str_check == 0 || not_exist_var == 2)
				all_in_str(&str, tmp->str);
			else
			if (str_check == 1)
				break ;
			// else
			// 	all_in_str(&str, "");
		}
		else if (msh->exp_current_type == LIMITER_HEREDOC)
		{
			if (ft_strlen(tmp->str) > 0)
				all_in_str(&str, tmp->str);
		}
		else if (msh->lexer_list->lexer_type == SPECIAL_VAR)
		{
			if (msh->exp_current_type == R_ORIGIN_REDIRECT || msh->exp_current_type == W_DEST_REDIRECT || msh->exp_current_type == WA_DEST_REDIRECT)
				all_in_str(&str, tmp->str);
			else
				all_in_str(&str, "");
		}
		else if (tmp && tmp->lexer_type >= 2 && tmp->lexer_type < 4)
		{
			if (msh->exp_current_type == R_ORIGIN_REDIRECT
				|| msh->exp_current_type == W_DEST_REDIRECT
				|| msh->exp_current_type == WA_DEST_REDIRECT)
			{
				if (str != NULL && not_exist_var == 1 && ft_strlen(tmp->str) == 0 && tmp->next == NULL)
				{
					str = NULL;
					str = ft_strdup("");
					not_exist_var = 0;
				}
				else if (str != NULL && not_exist_var == 1 && ft_strlen(tmp->str) > 0)
				{
					str = NULL;
					str = ft_strdup("");
					all_in_str(&str, tmp->str);
					not_exist_var = 0;
				}
				else if (str == NULL && not_exist_var == 1 && ft_strlen(tmp->str) > 0)
				{
					all_in_str(&str, tmp->str);
				}
			}
			else if (ft_strlen(tmp->str) > 0 && !str && not_exist_var == 1)
			{
				all_in_str(&str, tmp->str);
				not_exist_var = 0;
			}
			else if (ft_strlen(tmp->str) > 0 && str && not_exist_var == 1)
			{
				str = NULL;
				str = ft_strdup("");
				all_in_str(&str, tmp->str);
				not_exist_var = 0;
			}
			else if (not_exist_var == 0)
				all_in_str(&str, tmp->str);

		}
		else if (tmp->lexer_type == PIPE)
		{

			// expander_push(msh, ft_strdup("|"), PIPE_EXPANDED);
			break;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
		not_exist_var = 1;
	}
	if (tmp->lexer_type == PIPE)
	{
		expander_push(msh, str, msh->exp_current_type);
		expander_push(msh, ft_strdup("|"), PIPE_EXPANDED);
		// tmp = generate_str(msh, tmp);
	}
	else if (str && (not_exist_var == 2 || not_exist_var == 3))
	{
		expander_push(msh, str, AMBIGOUS_REDIRECT_EXP);
		msh->exp_current_type = WORD_EXPANDED;
	}
	else if (ft_strcmp(str, "\'\'") == 1)
	{
		expander_push(msh, str, msh->exp_current_type);
		msh->exp_current_type = WORD_EXPANDED;
	}
	else if (ft_strlen(str) > 0)
	{
		expander_push(msh, str, msh->exp_current_type);
		msh->exp_current_type = WORD_EXPANDED;
	}
	// else if (!str || str == NULL || ft_strlen(str) == 0)
	// 	expander_push(msh, "", WORD_EXPANDED);
	// free_chars(&str);//NE PEUT ETRE FREE AU RISQE DE CASSER LE HEREDOC
	return (tmp);
}
