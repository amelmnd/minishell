/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:58:49 by amennad           #+#    #+#             */
/*   Updated: 2023/10/26 10:59:14 by amennad          ###   ########.fr       */
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
			y = i;
			start = i;
			while (tmp->str[i] && tmp->str[i] != ' ' && tmp->str[i] != '\0'
				&& tmp->str[i + 1] != '\t')
			{
				y++;
				i++;
			}
			//TODO VERIFIER NOM DE LA VARAIBLE AVEC OU SANS $
			tmp->var_name = &(ft_substr(tmp->str, start, y))[1];
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
			//TODO VERIFIER NOM DE LA VARAIBLE AVEC OU SANS $
			tmp->var_name = &(tmp->str)[1];
			tmp->var_value = ft_getenv(msh, tmp->str);
		}
		else if (tmp->lexer_type == D_QUOTE_VAR)
		{
			dq_var_exist(msh, tmp);
		}
		tmp = tmp->next;
	}
}
