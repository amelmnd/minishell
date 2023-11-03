/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapt_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amennad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:13:51 by amennad           #+#    #+#             */
/*   Updated: 2023/10/30 16:00:14 by amennad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_msh_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

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
