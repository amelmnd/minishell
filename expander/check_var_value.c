/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:58:49 by amennad           #+#    #+#             */
/*   Updated: 2023/11/22 11:06:32 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dq_var_exist(t_msh *msh, t_lexer_list *tmp)
{
	int	i;
	int	y;
	int	start;

	i = 0;
	while (tmp->str[i])
	{
		if (tmp->str[i] == '$')
		{
			y = 0;
			start = i;
			while (tmp->str[i] && tmp->str[i] != ' ' && tmp->str[i] != '\0'
				&& tmp->str[i + 1] != '\t')
			{
				y++;
				i++;
			}
			tmp->var_name = ft_substr(tmp->str, start, y);
			tmp->var_value = ft_getenv(msh, ft_substr(tmp->str, start, y));
		}
		i++;
	}
}

void	check_var_value(t_msh *msh)
{
	t_lexer_list	*tmp;

	tmp = msh->lexer_list;
	while (tmp)
	{
		if (tmp->lexer_type == VARIABLE)
		{
			tmp->var_name = tmp->str;
			tmp->var_value = ft_getenv(msh, tmp->str);
		}
		else if (tmp->lexer_type == D_QUOTE_VAR)
			dq_var_exist(msh, tmp);
		else if (tmp->lexer_type == RETURN_VALUE)
			tmp->var_value = ft_itoa(msh->return_code);
		tmp = tmp->next;
	}
	free_lexer_list(tmp);
}
