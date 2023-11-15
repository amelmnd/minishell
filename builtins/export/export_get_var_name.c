/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_get_var_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:35:22 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 10:35:55 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_size_var_name(char *arg)
{
	int	size;
	int	i;

	size = 0;
	if (arg)
	{
		i = -1;
		while (arg[++i] && arg[i] != '=')
			size++;
	}
	return (size);
}

char	*export_get_var_name(char *arg)
{
	char	*var_name;
	int		size_var_name;
	int		i;

	var_name = NULL;
	if (arg)
	{
		size_var_name = get_size_var_name(arg);
		var_name = (char *)malloc(sizeof(char) * (size_var_name + 1));
		if (!var_name)
			return (NULL);
		i = -1;
		while (++i < size_var_name)
			var_name[i] = arg[i];
		var_name[i] = '\0';
	}
	return (var_name);
}
