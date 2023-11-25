/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   musical_chairs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 05:02:12 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/25 05:03:08 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	musical_chairs(t_msh *msh, char *start_str,
		t_lexer_list *tmp, char *end_str)
{
	free_chars(&(msh->temp));
	msh->temp = ft_strdup(msh->transexp);
	free_chars(&(msh->transexp));
	msh->transexp = ft_strjoin(start_str, tmp->var_value);
	free_chars(&(msh->temp));
	msh->temp = ft_strdup(msh->transexp);
	free_chars(&(msh->transexp));
	msh->transexp = ft_strjoin(msh->temp, end_str);
	free_chars(&(msh->temp));
}
