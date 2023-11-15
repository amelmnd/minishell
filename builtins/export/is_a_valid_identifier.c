/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_valid_identifier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:37:42 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 10:59:34 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_not_a_valid_chr(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (FALSE);
	return (TRUE);
}

t_bool	is_a_valid_identifier(char *var_name)
{
	int		i;

	if (ft_strlen(var_name))
	{
		if (!ft_isalpha(var_name[0]) && var_name[0] != '_')
			return (FALSE);
		i = 0;
		while (var_name[++i])
		{
			if (is_not_a_valid_chr(var_name[i]))
				return (FALSE);
		}
		return (TRUE);
	}
	else
		return (FALSE);
}
