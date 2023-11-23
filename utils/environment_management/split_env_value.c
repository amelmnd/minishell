/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:13:51 by amennad           #+#    #+#             */
/*   Updated: 2023/11/23 17:05:04 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_env_value(char *env_var, char **name, char **value)
{
	int		index;
	char	*tmp;

	index = 0;
	while (env_var[index] != '=')
		index++;
	*name = ft_substr(env_var, 0, index);
	tmp = ft_substr(env_var, index + 1, ft_strlen(env_var));
	*value = ft_strdup(tmp);
	free(tmp);
}
