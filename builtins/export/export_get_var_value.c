/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_get_var_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nstoutze <nstoutze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:50:18 by nstoutze          #+#    #+#             */
/*   Updated: 2023/11/15 10:50:27 by nstoutze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*export_get_var_value(char *var_name, char *arg)
{
	int		index_equal;
	char	*var_value;
	int		size_var_value;
	int		i;

	index_equal = is_chr_in_str(arg, '=');
	var_value = NULL;
	if (index_equal)
	{
		size_var_value = ft_strlen(arg) - ft_strlen(var_name) - 1;
		var_value = (char *)malloc(sizeof(char) * (size_var_value + 1));
		i = -1;
		while (++i < size_var_value)
			var_value[i] = arg[index_equal + 1 + i];
		var_value[size_var_value] = '\0';
		return (var_value);
	}
	return (ft_strdup(""));
}
