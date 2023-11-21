/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:04:31 by amennad           #+#    #+#             */
/*   Updated: 2023/11/21 07:13:51 by amennad          ###   ########.fr       */
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

/*
vérifier s'il n'est pas mieux de return un ft_strdup (en cas de variable trouvée)
pour éviter des problèmes de free ensuite
*/