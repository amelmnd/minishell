/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:04:31 by amennad           #+#    #+#             */
/*   Updated: 2023/11/25 05:21:54 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_msh *msh, char *env_var)
{
	t_env_list	*tmp;

	tmp = msh->env_list;
	while (tmp->next != NULL)
	{
		if (ft_strncmp(tmp->name, &env_var[1], ft_strlen(env_var)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	if (ft_strncmp(tmp->name, &env_var[1], ft_strlen(env_var)) == 0)
		return (tmp->value);
	return (NULL);
}
