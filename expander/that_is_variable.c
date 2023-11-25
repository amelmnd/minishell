/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   that_is_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:02:57 by amennad           #+#    #+#             */
/*   Updated: 2023/11/25 03:53:35 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_var_str(t_msh *msh, t_lexer_list *tmp, int *not_exist_var)
{
	while (tmp && (tmp->lexer_type == VARIABLE))
	{
		all_in_str(msh, tmp->var_name);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	if (tmp->next == NULL)
		*not_exist_var = 3;
	else
		*not_exist_var = 2;
}

void	norm_fn(t_msh *msh, t_lexer_list *tmp, int *not_exist_var,
		char **tmp_str)
{
	if (ft_strlen(msh->transexp) == 0)
	{
		all_in_str(msh, tmp->var_value);
		*not_exist_var = 0;
	}
	else
	{
		*tmp_str = ft_strdup("");
		all_in_str(msh, *tmp_str);
		*not_exist_var = 0;
	}
}

void	is_exist_var(t_msh *msh, t_lexer_list *tmp, int *not_exist_var)
{
	all_in_str(msh, tmp->var_value);
	*not_exist_var = 0;
}

void	is_biggest_condition(t_msh *msh, t_lexer_list *tmp, int *not_exist_var,
		char **tmp_str)
{
	if (tmp->var_value == NULL && *not_exist_var == 1 && ft_strlen(msh->transexp) == 0
		&& msh->transexp != NULL)
		all_in_str(msh, "");
	else if (tmp->var_value == NULL && *not_exist_var == 1 && ((tmp->next
				&& (tmp->next->lexer_type == D_QUOTE
					|| tmp->next->lexer_type == S_QUOTE)
				&& ft_strlen(tmp->next->str) == 0) || (tmp->previous
				&& (tmp->previous->lexer_type == D_QUOTE
					|| tmp->previous->lexer_type == S_QUOTE)
				&& ft_strlen(tmp->previous->str) == 0)))
		all_in_str(msh, "");
	else if (tmp->var_value == NULL && *not_exist_var == 1
		&& (ft_strlen(msh->transexp) == 0 || msh->transexp == NULL))
		create_var_str(msh, tmp, not_exist_var);
	else if (tmp->var_value == NULL && msh->transexp && *not_exist_var == 0)
		all_in_str(msh, "");
	else if (tmp->var_value && !(msh->transexp))
		is_exist_var(msh, tmp, not_exist_var);
	else if (tmp->var_value && msh->transexp && *not_exist_var == 1)
		norm_fn(msh, tmp, not_exist_var, tmp_str);
	else if (tmp->var_value)
		is_exist_var(msh, tmp, not_exist_var);
}

void	that_is_variable(t_msh *msh, t_lexer_list *tmp, int *not_exist_var)
{
	char	*tmp_str;

	if (msh->exp_current_type == LIMITER_HEREDOC)
		all_in_str(msh, tmp->var_name);
	else if (msh->exp_current_type == R_ORIGIN_REDIRECT
		|| msh->exp_current_type == W_DEST_REDIRECT
		|| msh->exp_current_type == WA_DEST_REDIRECT)
		is_biggest_condition(msh, tmp, not_exist_var, &tmp_str);
	else if (tmp->var_value)
		all_in_str(msh, tmp->var_value);
	else if (!tmp->var_value)
		all_in_str(msh, "");
}
